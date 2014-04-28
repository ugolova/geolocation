#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDir>
#include <QDebug>
#include <QTableWidget>
#include "container/serialization.h"
#include "container/algorithm.h"
#include "exceptions/unknown_station_exception.h"
#include "controller_gui.h"

using namespace std;

class MapCreator
{
private:
    static MapCreator *instance;

    MapCreator();
    ~MapCreator();

    QString defaultHtmlPath;
    QString routeHtmlPath;

    QString htmlTitle;
    QString mapApiUrl;
    QString jsMapVar;

    double mapCenterLat;
    double mapCenterLon;

    MultiGraph<double, Station> *container;
    QTableWidget *tableSearch;

    static QString getStationColor(int stationType);
    static QString getLineColor(int startStationType, int endStationType);

    void htmlHeader(QTextStream& out);
    void htmlFooter(QTextStream& out);

public:
    static MapCreator *getInstance();
    static bool deleteInstance();

    QString getDefaultHtmlPath();
    QString getRouteHtmlPath();

    MultiGraph<double, Station> *getContainer();
    void setContainer(MultiGraph<double, Station> *container);

    void setTableSearch(QTableWidget *tableSearch);

    void makeDefaultHTML(bool withLinks = true);
    void makeRouteHTML(QString stationA, QString stationB) throw(UnknownStationException);
};

#endif // MAPCREATOR_H
