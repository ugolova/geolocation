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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Импортировать файл"), "", tr("Files (*.*)"));
    qDebug() << "Importing file: " << fileName;

    MultiGraph<double, Station> *newContainer = Serialization::readObject(fileName.toStdString().c_str());

    MapCreator::getInstance()->setContainer(newContainer);
    MapCreator::getInstance()->makeDefaultHTML();

    delete container;
    container = newContainer;

    DynamicArray<Station> *stations = container->getVertexs();
    int arrSize = stations->getSize();
    for (int i = 0; i < arrSize; i++)
    {
        Station *st1 = stations->get(i);

        // filling stations table
        int rowNum = ui->table_stations->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(st1->getName());
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        ui->table_stations->insertRow(rowNum);
        ui->table_stations->setItem(rowNum, 0, newItem);

        // filling links table
        for (int j = 0; j < i; j++) {
            Station *st2 = stations->get(j);
            DynamicArray<double> *roads = container->getLenghtsByStation(st1, st2);

            for (int k = 0; k < roads->getSize(); k++) {

                int rowLinksNum = ui->table_links->rowCount();
                QTableWidgetItem *newLinkItem1 = new QTableWidgetItem(st1->getName());
                newItem->setFlags(newLinkItem1->flags() ^ Qt::ItemIsEditable);
                QTableWidgetItem *newLinkItem2 = new QTableWidgetItem(st2->getName());
                newItem->setFlags(newLinkItem2->flags() ^ Qt::ItemIsEditable);
                QTableWidgetItem *newLinkItem3 = new QTableWidgetItem(ControllerGUI::distanceToString(*roads->get(k)));
                newItem->setFlags(newLinkItem3->flags() ^ Qt::ItemIsEditable);
                QTableWidgetItem *newLinkItem4 = new QTableWidgetItem(QString::number(*roads->get(k)));
                newItem->setFlags(newLinkItem4->flags() ^ Qt::ItemIsEditable);

                ui->table_links->insertRow(rowLinksNum);
                ui->table_links->setItem(rowNum, 0, newLinkItem1);
                ui->table_links->setItem(rowNum, 1, newLinkItem2);
                ui->table_links->setItem(rowNum, 2, newLinkItem3);
                ui->table_links->setItem(rowNum, 3, newLinkItem4);

            }
        }

    }

    reloadAllBrowsers();
}

void MainWindow::exportFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Экспортировать в файл"), "", tr("Files (*.*)"));
    qDebug() << "Exporting to file: " << fileName;

    Serialization::writeObject(container, fileName.toStdString().c_str());
}

void MainWindow::on_button_search_clicked()
{
    try {
        MapCreator::getInstance()->setTableSearch(ui->table_route);

        qDebug() << "Making route from " << ui->lineEdit_from->text() << " to " << ui->lineEdit_to->text();

        while (ui->table_route->rowCount() > 0) {
            ui->table_route->removeRow(0);
        }

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

        // adding item to table
        int rowNum = ui->table_stations->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(ui->lineEdit_stationName->text());
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        ui->table_stations->insertRow(rowNum);
        ui->table_stations->setItem(rowNum, 0, newItem);

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

        // adding item to table
        int rowNum = ui->table_links->rowCount();
        QTableWidgetItem *newItem1 = new QTableWidgetItem(ui->lineEdit_stationA->text());
        newItem1->setFlags(newItem1->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(ui->lineEdit_stationB->text());
        newItem2->setFlags(newItem2->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *newItem3 = new QTableWidgetItem(ControllerGUI::distanceToString(length));
        newItem3->setFlags(newItem3->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *newItem4 = new QTableWidgetItem(QString::number(length));
        newItem3->setFlags(newItem4->flags() ^ Qt::ItemIsEditable);
        ui->table_links->insertRow(rowNum);
        ui->table_links->setItem(rowNum, 0, newItem1);
        ui->table_links->setItem(rowNum, 1, newItem2);
        ui->table_links->setItem(rowNum, 2, newItem3);
        ui->table_links->setItem(rowNum, 3, newItem4);

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
