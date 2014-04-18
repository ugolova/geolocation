#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "multigraph.h"
#include "road.h"

class Algorithm
{
public:
	static DynamicArray<Road>* findShortestPath(MultiGraph<double, Station>* graph);
};

#endif 
