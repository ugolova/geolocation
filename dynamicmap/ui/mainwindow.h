#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openLoginDialog();
    
private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
};

#endif // MAINWINDOW_H
