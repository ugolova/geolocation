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

    mapSearch = new MapCreator(SEARCH);
    mapSearch->makeHTML();
    QString mapSearchPath = "file:///" + QString(mapSearch->getMapFilePath());
    qDebug() << "mapSearchPath: " << mapSearchPath;
    ui->webView_search->load(QUrl(mapSearchPath));

    loginDialog = new LoginDialog();

    connect(ui->login, SIGNAL(triggered()), this, SLOT(openLoginDialog()));
    connect(ui->logout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(ui->import_file, SIGNAL(triggered()), this, SLOT(importFile()));
    connect(ui->export_file, SIGNAL(triggered()), this, SLOT(exportFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mapSearch;
    delete mapStations;
    delete mapLinks;
    delete loginDialog;
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
                mapStations = new MapCreator(STATIONS);
                mapStations->makeHTML();
                QString mapStationsPath = "file:///" + QString(mapStations->getMapFilePath());
                qDebug() << "mapStationsPath: " << mapStationsPath;
                ui->webView_stations->load(QUrl(mapStationsPath));
            }

            if (mapLinks == NULL) {
                mapLinks = new MapCreator(LINKS);
                mapLinks->makeHTML();
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
}

void MainWindow::exportFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Экспортировать в файл"), "", tr("Files (*.*)"));
    qDebug() << "Exporting to file: " << fileName;
}

void MainWindow::on_button_search_clicked()
{
    qDebug() << "Making route from " << ui->lineEdit_from->text() << " to " << ui->lineEdit_to->text();
    ui->webView_search->reload();
}

void MainWindow::on_button_addStation_clicked()
{
    qDebug() << "Added station: "
             << ui->lineEdit_stationName->text()
             << ", type: "
             << ui->comboBox_stationType->currentText()
             << ", lat: "
             << ui->lineEdit_stationLatitude->text()
             << ", lon: "
             << ui->lineEdit_stationLongitude->text();
    ui->webView_stations->reload();
}

void MainWindow::on_button_linkStations_clicked()
{
    qDebug() << "Added link: "
             << ui->comboBox_stationA->currentText()
             << " - "
             << ui->comboBox_stationB->currentText();
    ui->webView_links->reload();
}
