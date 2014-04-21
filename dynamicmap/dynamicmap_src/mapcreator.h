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

using namespace std;

enum MapMode { MAP_SEARCH, MAP_STATIONS, MAP_LINKS };
enum MakeMode { MAKE_DEFAULT, MAKE_SHORTEST_PATH };

class MapCreator
{
private:
    MapMode mode;
    string mapFilePath;
    string htmlTitle;
    string mapApiUrl;
    string jsMapVar;
    double mapCenterLat;
    double mapCenterLon;
    MultiGraph<double, Station> *container;
    QString pathStationA;
    QString pathStationB;


    void addStations(ofstream& out);
    void addLinks(ofstream& out);
    QString addShortestPath(ofstream& out);

public:
    MapCreator(MapMode mode);
    const char *getMapFilePath();
    QString makeHTML(MakeMode makeMode);
    void setContainer(MultiGraph<double, Station> *container);
    MultiGraph<double, Station> *getContainer();
    void setPathStationA(QString name);
    void setPathStationB(QString name);
};

#endif // MAPCREATOR_H
