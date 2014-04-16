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
    setWindowTitle(WINDOW_TITLE + " - anonymous");

    // Removing MANAGER-MODE tabs
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);

    ui->logout->setVisible(false);

    mapSearch = new MapCreator(SEARCH);
    mapSearch->makeHTML();
    QString mapSearchPath = QString("file://") + QString(mapSearch->getMapFilePath());
    qDebug("mapSearchPath: %s", mapSearchPath.toStdString().c_str());
    ui->webView_search->load(QUrl(mapSearchPath));

    loginDialog = new LoginDialog();

    connect(ui->login, SIGNAL(triggered()), this, SLOT(openLoginDialog()));
    connect(ui->logout, SIGNAL(triggered()), this, SLOT(logout()));
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
        qDebug("Login: %s, Password: %s", loginDialog->getUsername().toStdString().c_str(), loginDialog->getPassword().toStdString().c_str());
        bool authenticated = Authentication::auth(loginDialog->getUsername(), loginDialog->getPassword());
        if (authenticated) {
            ui->login->setVisible(false);
            ui->logout->setVisible(true);

            // Adding MANAGER-MODE tabs
            ui->tabWidget->insertTab(1, ui->tab_stations, "Станции");
            ui->tabWidget->insertTab(2, ui->tab_links, "Связи");

            setWindowTitle(WINDOW_TITLE + " - " + loginDialog->getUsername());

            if (mapStations == NULL) {
                mapStations = new MapCreator(STATIONS);
                mapStations->makeHTML();
                QString mapStationsPath = QString("file://") + QString(mapStations->getMapFilePath());
                qDebug("mapStationsPath: %s", mapStationsPath.toStdString().c_str());
                ui->webView_stations->load(QUrl(mapStationsPath));
            }

            if (mapLinks == NULL) {
                mapLinks = new MapCreator(LINKS);
                mapLinks->makeHTML();
                QString mapLinksPath = QString("file://") + QString(mapLinks->getMapFilePath());
                qDebug("mapLinksPath: %s", mapLinksPath.toStdString().c_str());
                ui->webView_links->load(QUrl(mapLinksPath));
            }
        }
    }
    loginDialog->resetForm();
}

void MainWindow::logout()
{
    ui->login->setVisible(true);
    ui->logout->setVisible(false);

    // Removing MANAGER-MODE tabs
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);

    setWindowTitle(WINDOW_TITLE + " - anonymous");
}

void MainWindow::on_button_search_clicked()
{
    ui->webView_search->reload();
}
