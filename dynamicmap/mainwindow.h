#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include "logindialog.h"
#include "mapcreator.h"
#include "authentication.h"

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
    void logout();
    void importFile();
    void exportFile();

private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
    MapCreator *mapSearch;
    MapCreator *mapStations;
    MapCreator *mapLinks;
    static const QString WINDOW_TITLE;
};

#endif // MAINWINDOW_H
