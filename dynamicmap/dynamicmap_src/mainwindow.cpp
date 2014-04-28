#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    WINDOW_TITLE("Динамическая карта РЖД/Метро"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(WINDOW_TITLE + " - " + Authentication::getCurrentUser());

    // Removing MANAGER-MODE tabs
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);

    ui->logout->setVisible(false);

    ui->table_links->setColumnHidden(3, true);

    loginDialog = new LoginDialog();
    container = new MultiGraph<double, Station>();

    MapCreator::getInstance()->setContainer(container);
    MapCreator::getInstance()->makeDefaultHTML();
    reloadAllBrowsers();

    connect(ui->login, SIGNAL(triggered()), this, SLOT(openLoginDialog()));
    connect(ui->logout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(ui->import_file, SIGNAL(triggered()), this, SLOT(importFile()));
    connect(ui->export_file, SIGNAL(triggered()), this, SLOT(exportFile()));

    // creating stations table context menu
    stationsTableSignalMapper = new QSignalMapper(this);
    connect(stationsTableSignalMapper, SIGNAL(mapped(int)), SLOT(deleteStation(int)));
    ui->table_stations->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table_stations, SIGNAL(customContextMenuRequested(QPoint)), SLOT(tableStationsMenuRequested(QPoint)));
    stationsContextMenu = new QMenu(this);
    deleteStationAction = new QAction("Удалить", this);
    stationsContextMenu->addAction(deleteStationAction);
    connect(deleteStationAction, SIGNAL(triggered()), stationsTableSignalMapper, SLOT(map()));

    // creating links table context menu
    linksTableSignalMapper = new QSignalMapper(this);
    connect(linksTableSignalMapper, SIGNAL(mapped(int)), SLOT(deleteLink(int)));
    ui->table_links->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table_links, SIGNAL(customContextMenuRequested(QPoint)), SLOT(tableLinksMenuRequested(QPoint)));
    linksContextMenu = new QMenu(this);
    deleteLinkAction = new QAction("Удалить", this);
    linksContextMenu->addAction(deleteLinkAction);
    connect(deleteLinkAction, SIGNAL(triggered()), linksTableSignalMapper, SLOT(map()));

}

MainWindow::~MainWindow()
{
    MapCreator::deleteInstance();

    delete ui;
    delete loginDialog;
    delete container;

    // deleting stations table context menu
    delete deleteStationAction;
    delete stationsContextMenu;
    delete stationsTableSignalMapper;

    // deleting links table context menu
    delete deleteLinkAction;
    delete linksContextMenu;
    delete linksTableSignalMapper;
}

void MainWindow::openLoginDialog()
{
    if (loginDialog->exec()) {
        qDebug() << "Login: " << loginDialog->getUsername() << ", Password: " << loginDialog->getPassword();
        bool authenticated = Authentication::auth(loginDialog->getUsername(), loginDialog->getPassword());
        if (authenticated) {
            ui->login->setVisible(false);
            ui->logout->setVisible(true);

            // Adding MANAGER-MODE tabs
            ui->tabWidget->insertTab(1, ui->tab_stations, "Редактор станций");
            ui->tabWidget->insertTab(2, ui->tab_links, "Редактор путей");

            setWindowTitle(WINDOW_TITLE + " - " + Authentication::getCurrentUser());

            qDebug() << "Logged in as " << Authentication::getCurrentUser();
        } else {
            qDebug() << "Incorrect login or password";
        }
    }
    loginDialog->resetForm();
}

void MainWindow::logout()
{
    Authentication::logout();

    ui->login->setVisible(true);
    ui->logout->setVisible(false);

    // Removing MANAGER-MODE tabs
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);

    setWindowTitle(WINDOW_TITLE + " - " + Authentication::getCurrentUser());

    qDebug() << "Logged out";
}

void MainWindow::importFile()
{
    try {

        QString fileName = QFileDialog::getOpenFileName(this, tr("Импортировать файл"), "", tr("Files (*.*)"));
        qDebug() << "Importing file: " << fileName;

        MultiGraph<double, Station> *newContainer = Serialization::readObject(fileName);

        MapCreator::getInstance()->setContainer(newContainer);
        MapCreator::getInstance()->makeDefaultHTML();

        delete container;
        container = newContainer;

        reloadAllBrowsers();

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::exportFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Экспортировать в файл"), "", tr("Files (*.*)"));
    qDebug() << "Exporting to file: " << fileName;

    Serialization::writeObject(container, fileName);
}

void MainWindow::on_button_search_clicked()
{
    try {
        MapCreator::getInstance()->setTableSearch(ui->table_route);

        qDebug() << "Making route from " << ui->lineEdit_from->text() << " to " << ui->lineEdit_to->text();

        clearTableData(ui->table_route);

        MapCreator::getInstance()->makeRouteHTML(ui->lineEdit_from->text(), ui->lineEdit_to->text());
        ui->webView_search->load(QUrl(MapCreator::getInstance()->getRouteHtmlPath()));

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::on_button_addStation_clicked()
{
    try {
        bool conversionSuccess;

        QString latString = ui->lineEdit_stationLatitude->text();
        double lat = latString.toDouble(&conversionSuccess);
        if (!conversionSuccess) {
            throw InvalidCoordinateException("широта", latString);
        }

        QString lonString = ui->lineEdit_stationLongitude->text();
        double lon = lonString.toDouble(&conversionSuccess);
        if (!conversionSuccess) {
            throw InvalidCoordinateException("долгота", lonString);
        }

        ControllerGUI::addStation(
                    container,
                    ui->lineEdit_stationName->text(),
                    ui->comboBox_stationType->currentIndex(),
                    lat,
                    lon);

        // reset form
        ui->lineEdit_stationName->setText("");
        ui->comboBox_stationType->setCurrentIndex(0);
        ui->lineEdit_stationLatitude->setText("");
        ui->lineEdit_stationLongitude->setText("");

        // update maps
        MapCreator::getInstance()->makeDefaultHTML();
        reloadAllBrowsers();

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::on_button_linkStations_clicked()
{
    try {
        double length = -1;
        if (ui->checkBox_manualDistance->isChecked()) {

            bool conversionSuccess;

            length = ui->lineEdit_distance->text().toDouble(&conversionSuccess);
            if (!conversionSuccess) {
                throw InvalidDistanceException(ui->lineEdit_distance->text());
            }
        }

        length = ControllerGUI::addLink(
                    container,
                    ui->lineEdit_stationA->text(),
                    ui->lineEdit_stationB->text(),
                    length);

        // reset form
        ui->lineEdit_stationA->setText("");
        ui->lineEdit_stationB->setText("");

        // update maps
        MapCreator::getInstance()->makeDefaultHTML();
        reloadAllBrowsers();

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::tableStationsMenuRequested(QPoint pos)
{
    stationsTableSignalMapper->setMapping(deleteStationAction, ui->table_stations->indexAt(pos).row());
    stationsContextMenu->popup(ui->table_stations->viewport()->mapToGlobal(pos));
}

void MainWindow::tableLinksMenuRequested(QPoint pos)
{
    linksTableSignalMapper->setMapping(deleteLinkAction, ui->table_links->indexAt(pos).row());
    linksContextMenu->popup(ui->table_links->viewport()->mapToGlobal(pos));
}

void MainWindow::deleteStation(int row)
{
    ControllerGUI::delStation(
                container,
                ui->table_stations->model()->index(row, 0).data().toString());
    ui->table_stations->removeRow(row);

    MapCreator::getInstance()->makeDefaultHTML();
    reloadAllBrowsers();
}

void MainWindow::deleteLink(int row)
{
    try {
        ControllerGUI::delLink(
                    container,
                    ui->table_links->model()->index(row, 0).data().toString(),
                    ui->table_links->model()->index(row, 1).data().toString(),
                    ui->table_links->model()->index(row, 3).data().toDouble());
        ui->table_links->removeRow(row);

        MapCreator::getInstance()->makeDefaultHTML();
        reloadAllBrowsers();

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::on_checkBox_manualDistance_stateChanged()
{
    if (ui->checkBox_manualDistance->isChecked()) {
        ui->lineEdit_distance->setEnabled(true);
    } else {
        ui->lineEdit_distance->setEnabled(false);
    }
}

void MainWindow::reloadAllBrowsers()
{
    QString defaultHTML = MapCreator::getInstance()->getDefaultHtmlPath();
    ui->webView_search->load(QUrl(defaultHTML));
    ui->webView_stations->load(QUrl(defaultHTML));
    ui->webView_links->load(QUrl(defaultHTML));
}

void MainWindow::on_button_findStationToDel_clicked()
{
    try {
        clearTableData(ui->table_stations);

        Station *st = ControllerGUI::getStationByName(container, ui->lineEdit_delStationName->text(), false);
        if (st == NULL) {
            throw UnknownStationException(ui->lineEdit_delStationName->text());
        }

        // adding item to table
        int rowNum = ui->table_stations->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(st->getName());
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        ui->table_stations->insertRow(rowNum);
        ui->table_stations->setItem(rowNum, 0, newItem);

        // reset form
        ui->lineEdit_delStationName->setText("");

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::on_button_findLinkToDel_clicked()
{
    try {
        clearTableData(ui->table_links);

        Station *stA = ControllerGUI::getStationByName(container, ui->lineEdit_delStationA->text(), false);
        if (stA == NULL) {
            throw UnknownStationException(ui->lineEdit_delStationA->text());
        }

        Station *stB = ControllerGUI::getStationByName(container, ui->lineEdit_delStationB->text(), false);
        if (stB == NULL) {
            throw UnknownStationException(ui->lineEdit_delStationB->text());
        }

        DynamicArray<double> *roads = container->getLenghtsByStation(stA, stB);
        if (roads == 0 || roads->getSize() < 1) {
            throw UnknownLinkException(ui->lineEdit_delStationA->text(), ui->lineEdit_delStationB->text(), 0);
        }

        for (int i = 0; i < roads->getSize(); i++) {

            int rowLinksNum = ui->table_links->rowCount();
            QTableWidgetItem *newLinkItem1 = new QTableWidgetItem(stA->getName());
            newLinkItem1->setFlags(newLinkItem1->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem *newLinkItem2 = new QTableWidgetItem(stB->getName());
            newLinkItem2->setFlags(newLinkItem2->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem *newLinkItem3 = new QTableWidgetItem(ControllerGUI::distanceToString(*roads->get(i)));
            newLinkItem3->setFlags(newLinkItem3->flags() ^ Qt::ItemIsEditable);
            QTableWidgetItem *newLinkItem4 = new QTableWidgetItem(QString::number(*roads->get(i)));
            newLinkItem4->setFlags(newLinkItem4->flags() ^ Qt::ItemIsEditable);

            ui->table_links->insertRow(rowLinksNum);
            ui->table_links->setItem(rowLinksNum, 0, newLinkItem1);
            ui->table_links->setItem(rowLinksNum, 1, newLinkItem2);
            ui->table_links->setItem(rowLinksNum, 2, newLinkItem3);
            ui->table_links->setItem(rowLinksNum, 3, newLinkItem4);

        }

        // reset form
        ui->lineEdit_delStationA->setText("");
        ui->lineEdit_delStationB->setText("");

    } catch (const DynamicMapException& e) {
        qDebug() << e.getMsg();
        QMessageBox msgBox;
        msgBox.setText(e.getMsg());
        msgBox.exec();
    }
}

void MainWindow::clearTableData(QTableWidget *table)
{
    while (table->rowCount() > 0) {
        table->removeRow(0);
    }
}
