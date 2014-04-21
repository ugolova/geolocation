#include "algorithm.h"


Station* Algorithm::getStationByName(MultiGraph<double, Station>* graph, std::string name)
{
    DynamicArray<Station> *stations = graph->getVertexs();
    for (int i = 0; i < stations->getSize(); i++)
    {
        Station *curStation = stations->get(i);
         if (curStation->getName().compare(name) == 0)
         {
             return curStation;
         }
    }
}

DynamicArray<Road>* Algorithm::findShortestPath(MultiGraph<double, Station>* graph, std::string stationA, std::string stationB)
{
    Station *start = getStationByName(graph, stationA);
    Station *end = getStationByName(graph, stationB);
    DynamicArray<Station> *stations = graph->getVertexs();
    if (stations->getIndex(start) != -1 && stations->getIndex(end) != -1)
    {
        //TODO
    }
    return 0;
}
