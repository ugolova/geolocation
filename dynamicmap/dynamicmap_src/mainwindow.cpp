#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    WINDOW_TITLE("Динамическая карта РЖД/Метро"),
    ui(new Ui::MainWindow),
    mapSearch(NULL),
    mapEdit(NULL)
{
    ui->setupUi(this);
    setWindowTitle(WINDOW_TITLE + " - " + Authentication::getCurrentUser());

    // Removing MANAGER-MODE tabs
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);

    ui->logout->setVisible(false);

    loginDialog = new LoginDialog();
    container = new MultiGraph<double, Station>();

    mapSearch = new MapCreator("search");
    mapSearch->setContainer(container);
    mapSearch->makeDefaultHTML();
    QString mapSearchPath = "file:///" + mapSearch->getMapFilePath();
    qDebug() << "mapSearchPath: " << mapSearchPath;
    ui->webView_search->load(QUrl(mapSearchPath));

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
    delete ui;
    delete loginDialog;
    delete mapSearch;
    delete mapEdit;
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

            if (mapEdit == NULL) {
                mapEdit = new MapCreator("edit");
                mapEdit->setContainer(container);
                mapEdit->makeDefaultHTML();
                QString mapEditPath = "file:///" + mapEdit->getMapFilePath();
                qDebug() << "mapStationsPath: " << mapEditPath;
                ui->webView_stations->load(QUrl(mapEditPath));
                ui->webView_links->load(QUrl(mapEditPath));
            }
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

    mapSearch->setContainer(newContainer);
    if (mapEdit != NULL) {
        mapEdit->setContainer(newContainer);
    }

    mapSearch->makeDefaultHTML();
    if (mapEdit != NULL) {
        mapEdit->makeDefaultHTML();
    }

    delete container;
    container = newContainer;


    DynamicArray<Station> *stations = container->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        int rowNum = ui->table_stations->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(stations->get(i)->getName());
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        ui->table_stations->insertRow(rowNum);
        ui->table_stations->setItem(rowNum, 0, newItem);
    }
    /*QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
    sort_filter->setSourceModel(ui->table_stations->model());
    sort_filter->sort(0);
    ui->table_stations->setModel(sort_filter);*/

    ui->webView_search->reload();
    ui->webView_stations->reload();
    ui->webView_links->reload();
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
        mapSearch->setTableSearch(ui->table_route);

        qDebug() << "Making route from " << ui->lineEdit_from->text() << " to " << ui->lineEdit_to->text();

        while (ui->table_route->rowCount() > 0) {
            ui->table_route->removeRow(0);
        }

        mapSearch->makeRouteHTML(ui->lineEdit_from->text(), ui->lineEdit_to->text());
        ui->webView_search->reload();

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
        mapEdit->makeDefaultHTML();
        ui->webView_stations->reload();
        ui->webView_links->reload();

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
        bool conversionSuccess;

        QString distanceString = ui->lineEdit_distance->text();
        double distance = distanceString.toDouble(&conversionSuccess);
        if (!conversionSuccess) {
            throw InvalidDistanceException(distanceString);
        }

        ControllerGUI::addLink(
                    container,
                    ui->lineEdit_stationA->text(),
                    ui->lineEdit_stationB->text(),
                    distance);

        // adding item to table
        int rowNum = ui->table_links->rowCount();
        QTableWidgetItem *newItem1 = new QTableWidgetItem(ui->lineEdit_stationA->text());
        newItem1->setFlags(newItem1->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(ui->lineEdit_stationB->text());
        newItem2->setFlags(newItem2->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *newItem3 = new QTableWidgetItem(distanceString);
        newItem3->setFlags(newItem3->flags() ^ Qt::ItemIsEditable);
        ui->table_links->insertRow(rowNum);
        ui->table_links->setItem(rowNum, 0, newItem1);
        ui->table_links->setItem(rowNum, 1, newItem2);
        ui->table_links->setItem(rowNum, 2, newItem3);

        // reset form
        ui->lineEdit_stationA->setText("");
        ui->lineEdit_stationB->setText("");
        ui->lineEdit_distance->setText("");

        // update maps
        mapEdit->makeDefaultHTML();
        ui->webView_stations->reload();
        ui->webView_links->reload();

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
    mapEdit->makeDefaultHTML();
    ui->webView_stations->reload();
    ui->webView_links->reload();
}

void MainWindow::deleteLink(int row)
{
    ControllerGUI::delLink(
                container,
                ui->table_links->model()->index(row, 0).data().toString(),
                ui->table_links->model()->index(row, 1).data().toString(),
                ui->table_links->model()->index(row, 2).data().toDouble());
    ui->table_links->removeRow(row);
    mapEdit->makeDefaultHTML();
    ui->webView_stations->reload();
    ui->webView_links->reload();
}
