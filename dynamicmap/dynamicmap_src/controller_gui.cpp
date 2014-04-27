#include "controller_gui.h"

ControllerGUI::ControllerGUI()
{
}

double ControllerGUI::getDistanceBetweenCoordinates(double lat1, double lon1, double lat2, double lon2)
{
    double lat1p = lat1 * M_PI / 180.0;
    double lng1p = lon1 * M_PI / 180.0;
    double lat2p = lat2 * M_PI / 180.0;
    double lng2p = lon2 * M_PI / 180.0;
    double res = 6372.795 * 2.0 * asin(sqrt(
                                     sin((lat2p - lat1p) / 2.0) * sin((lat2p - lat1p) / 2.0) +
                                     cos(lat1p) * cos(lat2p) * sin((lng2p - lng1p) / 2.0) * sin((lng2p - lng1p) / 2.0)
                                     ));
    // precision workaround
    return QString::number(res).toDouble();
}

Station* ControllerGUI::getStationByName(MultiGraph<double, Station>* graph, QString name, bool exact)
{
    Qt::CaseSensitivity cs;
    if (exact) {
        cs = Qt::CaseSensitive;
    } else {
        cs = Qt::CaseInsensitive;
    }

    DynamicArray<Station> *stations = graph->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        Station *curStation = stations->get(i);

        if (curStation->getName().compare(name, cs) == 0)
        {
            return curStation;
        }
    }
    return NULL;
}

void ControllerGUI::addStation(MultiGraph<double, Station>* graph, QString name, int type, double lat, double lon)
{
    Station *st = new Station(name, lon, lat, type);
    graph->addVertex(st);
}

void ControllerGUI::delStation(MultiGraph<double, Station>* graph, QString name)
{
    Station *st = getStationByName(graph, name);
    if (st != NULL) {
        graph->removeVertex(st);
    }
}

double ControllerGUI::addLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length) throw(UnknownStationException)
{
    Station *stA = getStationByName(graph, stationA);
    if (stA == NULL) {
        throw UnknownStationException(stationA);
    }

    Station *stB = getStationByName(graph, stationB);
    if (stB == NULL) {
        throw UnknownStationException(stationB);
    }

    if (length == -1) {
        length = getDistanceBetweenCoordinates(stA->getLatitude(), stA->getLongitude(), stB->getLatitude(), stB->getLongitude());
    }

    // forward direction
    graph->addPathToVertex(stA, stB, new double(length));

    // reverse direction
    graph->addPathToVertex(stB, stA, new double(length));

    return length;
}

void ControllerGUI::delLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length) throw(DynamicMapException)
{
    Station *stA = getStationByName(graph, stationA);
    if (stA == NULL) {
        throw UnknownStationException(stationA);
    }

    Station *stB = getStationByName(graph, stationB);
    if (stB == NULL) {
        throw UnknownStationException(stationB);
    }

    // forward direction
    bool result = graph->removePathFromVertex(stA, stB, new double(length));
    if (!result) {
        throw UnknownLinkException(stationA, stationB, length);
    }

    // reverse direction
    result = graph->removePathFromVertex(stB, stA, new double(length));
    if (!result) {
        throw UnknownLinkException(stationB, stationA, length);
    }
}

QString ControllerGUI::distanceToString(double distance)
{
    return QString::number(round(distance * 10) / 10);
}
