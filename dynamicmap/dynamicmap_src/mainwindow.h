#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include "logindialog.h"
#include "mapcreator.h"
#include "authentication.h"
#include "controller_gui.h"
#include <QModelIndex>
#include <QSignalMapper>
#include <QMessageBox>

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
    void logout();
    void importFile();
    void exportFile();
    void on_button_search_clicked();
    void on_button_addStation_clicked();
    void on_button_linkStations_clicked();
    void tableStationsMenuRequested(QPoint pos);
    void deleteStation(int row);

private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
    MapCreator *mapSearch;
    MapCreator *mapStations;
    MapCreator *mapLinks;
    static const QString WINDOW_TITLE;
    MultiGraph<double, Station> *container;
    QMenu *stationsContextMenu;
    QAction *deleteStationAction;
    QSignalMapper *signalMapper;
};

#endif // MAINWINDOW_H
