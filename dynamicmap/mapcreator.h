#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MapCreator
{
public:
    MapCreator();
    static const char* getMapFilename();
    void writeHTML();

private:
    static const string MAP_FILENAME;
    static const string HTML_TITLE;
    static const string MAP_API_URL;
    static const string JS_MAP_VAR;
    static const double MAP_CENTER_LAT;
    static const double MAP_CENTER_LON;
    void addStation(ofstream out);
    void addLink(ofstream out);
};

#endif // MAPCREATOR_H
