#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QModelIndex>
#include <QSignalMapper>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "logindialog.h"
#include "mapcreator.h"
#include "authentication.h"
#include "controller_gui.h"
#include "exceptions/invalid_coordinate_exception.h"
#include "exceptions/unknown_link_exception.h"
#include "exceptions/invalid_distance_exception.h"

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
    void tableLinksMenuRequested(QPoint pos);
    void deleteStation(int row);
    void deleteLink(int row);
    void on_checkBox_manualDistance_stateChanged();
    void on_button_findStationToDel_clicked();

    void on_button_findLinkToDel_clicked();

private:
    const QString WINDOW_TITLE;
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
    MultiGraph<double, Station> *container;
    QMenu *stationsContextMenu;
    QAction *deleteStationAction;
    QSignalMapper *stationsTableSignalMapper;
    QMenu *linksContextMenu;
    QAction *deleteLinkAction;
    QSignalMapper *linksTableSignalMapper;

    void reloadAllBrowsers();
    void clearTableData(QTableWidget *table);
};

#endif // MAINWINDOW_H
