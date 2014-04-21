#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDir>
#include <container/serialization.h>
#include <container/algorithm.h>
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

    void addStations(ofstream& out);
    void addLinks(ofstream& out);
    void addShortestPath(ofstream& out);

public:
    MapCreator(MapMode mode);
    const char *getMapFilePath();
    void makeHTML(MakeMode makeMode);
    void setContainer(MultiGraph<double, Station> *container);
    MultiGraph<double, Station> *getContainer();
};

#endif // MAPCREATOR_H
