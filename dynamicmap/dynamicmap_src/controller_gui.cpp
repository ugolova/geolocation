#include "controller_gui.h"

ControllerGUI::ControllerGUI()
{
}

Station* ControllerGUI::getStationByName(MultiGraph<double, Station>* graph, QString name)
{
    DynamicArray<Station> *stations = graph->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        Station *curStation = stations->get(i);
        if (curStation->getName().compare(name.toStdString()) == 0)
        {
            return curStation;
        }
    }
    return NULL;
}

void ControllerGUI::addStation(MultiGraph<double, Station>* graph, QString name, int type, QString lat, QString lon)
{
    Station *st = new Station(name.toStdString(), lon.toDouble(), lat.toDouble(), type);
    graph->addVertex(st);
}

void ControllerGUI::delStation(MultiGraph<double, Station>* graph, QString name)
{
    DynamicArray<Station> *stations = graph->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        Station *curStation = stations->get(i);
        if (curStation->getName().compare(name.toStdString()) == 0)
        {
            graph->removeVertex(curStation);
            return;
        }
    }
}
