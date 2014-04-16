#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <QDir>

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

    void addStations(ofstream& out);
    void addLinks(ofstream& out);

public:
    MapCreator(MapMode mode);
    const char* getMapFilePath();
    void makeHTML();
};

#endif // MAPCREATOR_H
