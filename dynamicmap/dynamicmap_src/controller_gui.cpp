#include "controller_gui.h"

ControllerGUI::ControllerGUI()
{
}

Station* ControllerGUI::getStationByName(MultiGraph<double, Station>* graph, QString name, bool exact)
{
    DynamicArray<Station> *stations = graph->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        Station *curStation = stations->get(i);

        if (QString::compare(name,curStation->getName(),Qt::CaseInsensitive) == 0)
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

void ControllerGUI::addLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length) throw(UnknownStationException)
{
    Station *stA = getStationByName(graph, stationA);
    if (stA == NULL) {
        throw UnknownStationException(stationA);
    }

    Station *stB = getStationByName(graph, stationB);
    if (stB == NULL) {
        throw UnknownStationException(stationB);
    }

    graph->addPathToVertex(stA, stB, new double(length));
}

void ControllerGUI::delLink(MultiGraph<double, Station>* graph, QString stationA, QString stationB, double length)
{
    Station *stA = getStationByName(graph, stationA);
    Station *stB = getStationByName(graph, stationB);
    if (stA != NULL && stB != NULL) {
        graph->removePathFromVertex(stA, stB, &length);
    }
}
