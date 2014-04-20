#include "algorithm.h"


DynamicArray<Road>* Algorithm::findShortestPath(MultiGraph<double, Station>* graph, Station* start, Station* end)
{
	DynamicArray<Station> *stations = graph->getVertexs();
	if (stations->getIndex(start) != -1 && stations->getIndex(end) != -1)
	{
		//TODO
	}
	return 0;
}
