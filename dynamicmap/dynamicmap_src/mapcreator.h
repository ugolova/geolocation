#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDir>
#include <container/serialization.h>
#include <container/algorithm.h>
#include "controller_gui.h"
#include <QDebug>
#include <QTableWidget>

using namespace std;

enum MapMode { MAP_SEARCH, MAP_STATIONS, MAP_LINKS };
enum MakeMode { MAKE_DEFAULT, MAKE_SHORTEST_PATH };

class MapCreator
{
private:
    MapMode mode;
    QString mapFilePath;
    QString htmlTitle;
    QString mapApiUrl;
    QString jsMapVar;
    double mapCenterLat;
    double mapCenterLon;
    MultiGraph<double, Station> *container;
    QString pathStationA;
    QString pathStationB;
    QTableWidget *tableSearch;

    void addStations(QTextStream& out, bool withLinks);
    QString addShortestPath(QTextStream& out);
    std::string getStationColor(int stationType);
    std::string getLineColor(int startStationType, int endStationType);

public:
    MapCreator(MapMode mode);
    QString getMapFilePath();
    QString makeHTML(MakeMode makeMode);
    void setContainer(MultiGraph<double, Station> *container);
    MultiGraph<double, Station> *getContainer();
    void setPathStationA(QString name);
    void setPathStationB(QString name);
    void setTableSearch(QTableWidget *tableSearch);
};

#endif // MAPCREATOR_H
