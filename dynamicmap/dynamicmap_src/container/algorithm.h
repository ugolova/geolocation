#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "multigraph.h"
#include "road.h"

using namespace container;

class Algorithm
{
public:
	static DynamicArray<Road>* findShortestPath(MultiGraph<double, Station>* graph, Station* start, Station* end);
};



#endif // ALGORITHM_H
