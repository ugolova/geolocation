#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "multigraph.h"
#include "road.h"
#include "station.h"

using namespace container;

class Algorithm
{
public:
    static Station* getStationByName(MultiGraph<double, Station>* graph, std::string name);
    static DynamicArray<Road>* findShortestPath(MultiGraph<double, Station>* graph, std::string stationA, std::string stationB);
};



#endif // ALGORITHM_H
