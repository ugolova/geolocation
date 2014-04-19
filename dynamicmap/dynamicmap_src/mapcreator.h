#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDir>
#include <container/serialization.h>
#include <QDebug>

using namespace std;

enum MapMode { SEARCH, STATIONS, LINKS };

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

    void addStations(ofstream& out);
    void addLinks(ofstream& out);

public:
    MapCreator(MapMode mode);
    const char *getMapFilePath();
    void makeHTML();
    void setContainer(MultiGraph<double, Station> *container);
    MultiGraph<double, Station> *getContainer();
};

#endif // MAPCREATOR_H
