#ifndef CONTROLLER_GUI_H
#define CONTROLLER_GUI_H

#include <QString>
#include "container/multigraph.h"
#include "container/station.h"
#include "container/road.h"
#include "exceptions/unknown_station_exception.h"

using namespace container;

class ControllerGUI
{
private:
    ControllerGUI();
public:
    static Station* getStationByName(MultiGraph<double, Station>* graph, QString name, bool exact = true);
    static void addStation(MultiGraph<double, Station>* graph, QString name, int type, double lat, double lon);
    static void delStation(MultiGraph<double, Station>* graph, QString name);
    static void addLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length) throw(UnknownStationException);
    static void delLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length);
};

#endif // CONTROLLER_GUI_H
