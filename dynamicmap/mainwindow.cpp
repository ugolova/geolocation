#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MapCreator mapCreator = MapCreator();
    mapCreator.writeHTML();

    QString mapPath = QString("file:///") + QDir::current().absolutePath() + QDir::separator() + QString(MapCreator::getMapFilename());
    qDebug("MapPath: %s", mapPath.toLatin1().data());
    ui->webView_search->load(QUrl(mapPath));
    ui->webView_stations->load(QUrl(mapPath));
    ui->webView_links->load(QUrl(mapPath));



    connect(ui->login, SIGNAL(triggered()), this, SLOT(openLoginDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
