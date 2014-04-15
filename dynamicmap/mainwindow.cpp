#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
