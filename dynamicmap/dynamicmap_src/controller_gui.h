#ifndef CONTROLLER_GUI_H
#define CONTROLLER_GUI_H

#include <QString>
#include <cmath>
#include "container/multigraph.h"
#include "container/station.h"
#include "container/road.h"
#include "exceptions/unknown_station_exception.h"
#include "exceptions/unknown_link_exception.h"

using namespace container;

class ControllerGUI
{
private:
    ControllerGUI();
    static double getDistanceBetweenCoordinates(double lat1, double lon1, double lat2, double lon2);
public:
    static Station* getStationByName(MultiGraph<double, Station>* graph, QString name, bool exact = true);
    static void addStation(MultiGraph<double, Station>* graph, QString name, int type, double lat, double lon);
    static void delStation(MultiGraph<double, Station>* graph, QString name);
    static double addLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length = -1) throw(UnknownStationException);
    static void delLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length) throw(DynamicMapException);
    static QString distanceToString(double distance);
};

#endif // CONTROLLER_GUI_H
