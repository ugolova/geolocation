#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::WINDOW_TITLE = "Динамическая карта РЖД/Метро";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mapSearch(NULL),
    mapStations(NULL),
    mapLinks(NULL)
{
    ui->setupUi(this);
    setWindowTitle(WINDOW_TITLE + " - " + Authentication::getCurrentUser());

    // Removing MANAGER-MODE tabs
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);

    ui->logout->setVisible(false);

    loginDialog = new LoginDialog();
    container = new MultiGraph<double, Station>();

    mapSearch = new MapCreator(MAP_SEARCH);
    mapSearch->setContainer(container);
    mapSearch->makeHTML(MAKE_DEFAULT);
    QString mapSearchPath = "file:///" + QString(mapSearch->getMapFilePath());
    qDebug() << "mapSearchPath: " << mapSearchPath;
    ui->webView_search->load(QUrl(mapSearchPath));

    connect(ui->login, SIGNAL(triggered()), this, SLOT(openLoginDialog()));
    connect(ui->logout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(ui->import_file, SIGNAL(triggered()), this, SLOT(importFile()));
    connect(ui->export_file, SIGNAL(triggered()), this, SLOT(exportFile()));

    // signal mapper
    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), SLOT(deleteStation(int)));

    // stations table context menu
    ui->table_stations->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->table_stations, SIGNAL(customContextMenuRequested(QPoint)), SLOT(tableStationsMenuRequested(QPoint)));

    // stations table context menu items
    stationsContextMenu = new QMenu(this);
    deleteStationAction = new QAction("Удалить", this);
    stationsContextMenu->addAction(deleteStationAction);
    connect(deleteStationAction, SIGNAL(triggered()), signalMapper, SLOT(map()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete mapSearch;
    delete mapStations;
    delete mapLinks;
    delete loginDialog;
    delete container;
    delete stationsContextMenu;
    delete deleteStationAction;
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
            ui->tabWidget->insertTab(1, ui->tab_stations, "Станции");
            ui->tabWidget->insertTab(2, ui->tab_links, "Связи");

            setWindowTitle(WINDOW_TITLE + " - " + Authentication::getCurrentUser());

            if (mapStations == NULL) {
                mapStations = new MapCreator(MAP_STATIONS);
                mapStations->setContainer(container);
                mapStations->makeHTML(MAKE_DEFAULT);
                QString mapStationsPath = "file:///" + QString(mapStations->getMapFilePath());
                qDebug() << "mapStationsPath: " << mapStationsPath;
                ui->webView_stations->load(QUrl(mapStationsPath));
            }

            if (mapLinks == NULL) {
                mapLinks = new MapCreator(MAP_LINKS);
                mapLinks->setContainer(container);
                mapLinks->makeHTML(MAKE_DEFAULT);
                QString mapLinksPath = "file:///" + QString(mapLinks->getMapFilePath());
                qDebug() << "mapLinksPath: " << mapLinksPath;
                ui->webView_links->load(QUrl(mapLinksPath));
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
    if (mapStations != NULL) {
        mapStations->setContainer(newContainer);
    }
    if (mapLinks != NULL) {
        mapLinks->setContainer(newContainer);
    }

    mapSearch->makeHTML(MAKE_DEFAULT);
    if (mapStations != NULL) {
        mapStations->makeHTML(MAKE_DEFAULT);
    }
    if (mapLinks != NULL) {
        mapLinks->makeHTML(MAKE_DEFAULT);
    }

    delete container;
    container = newContainer;


    DynamicArray<Station> *stations = container->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        int rowNum = ui->table_stations->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(stations->get(i)->getName()));
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        ui->table_stations->insertRow(rowNum);
        ui->table_stations->setItem(rowNum, 0, newItem);
    }

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
    qDebug() << "Making route from " << ui->lineEdit_from->text() << " to " << ui->lineEdit_to->text();
    ui->webView_search->reload();
}

void MainWindow::on_button_addStation_clicked()
{
    ControllerGUI::addStation(
                container,
                ui->lineEdit_stationName->text(),
                ui->comboBox_stationType->currentIndex(),
                ui->lineEdit_stationLatitude->text(),
                ui->lineEdit_stationLongitude->text());

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

    // update map
    mapStations->makeHTML(MAKE_DEFAULT);
    ui->webView_stations->reload();
}

void MainWindow::on_button_linkStations_clicked()
{
    qDebug() << "Added link: "
             << ui->lineEdit_stationA->text()
             << " - "
             << ui->lineEdit_stationB->text();
    ui->webView_links->reload();
}

void MainWindow::tableStationsMenuRequested(QPoint pos)
{
    signalMapper->setMapping(deleteStationAction, ui->table_stations->indexAt(pos).row());
    stationsContextMenu->popup(ui->table_stations->viewport()->mapToGlobal(pos));
}

void MainWindow::deleteStation(int row)
{
    ControllerGUI::delStation(
                container,
                ui->table_stations->model()->index(row, 0).data().toString());
    ui->table_stations->removeRow(row);
    mapStations->makeHTML(MAKE_DEFAULT);
    ui->webView_stations->reload();
}
