#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include "logindialog.h"
#include "mapcreator.h"

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
    
private slots:
    void on_button_search_clicked();

private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
};

#endif // MAINWINDOW_H
