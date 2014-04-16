#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mapSearch = new MapCreator(SEARCH);
    mapSearch->makeHTML();
    QString mapSearchPath = QString("file://") + QString(mapSearch->getMapFilePath());
    qDebug("mapSearchPath: %s", mapSearchPath.toLatin1().data());
    ui->webView_search->load(QUrl(mapSearchPath));

    mapStations = new MapCreator(STATIONS);
    mapStations->makeHTML();
    QString mapStationsPath = QString("file://") + QString(mapStations->getMapFilePath());
    qDebug("mapStationsPath: %s", mapStationsPath.toLatin1().data());
    ui->webView_stations->load(QUrl(mapStationsPath));

    mapLinks = new MapCreator(LINKS);
    mapLinks->makeHTML();
    QString mapLinksPath = QString("file://") + QString(mapLinks->getMapFilePath());
    qDebug("mapLinksPath: %s", mapLinksPath.toLatin1().data());
    ui->webView_links->load(QUrl(mapLinksPath));

    connect(ui->login, SIGNAL(triggered()), this, SLOT(openLoginDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mapSearch;
    delete mapStations;
    delete mapLinks;
}

void MainWindow::openLoginDialog()
{
    if (loginDialog == 0) {
        loginDialog = new LoginDialog();
    }
    loginDialog->show();
}

void MainWindow::on_button_search_clicked()
{
    ui->webView_search->reload();
}
