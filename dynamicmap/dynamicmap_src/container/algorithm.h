#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "multigraph.h"
#include "road.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace container;

class Algorithm
{
private:
	static double findMin(DynamicArray<double> * arr);
	
	typedef std::vector<std::vector<std::pair<int, float> > > Graph;
	class Comparator
	{
	public:
		int operator() (const std::pair<int, float>& p1, const std::pair<int, float> &p2)
		{
			return p1.second>p2.second;
		}
	};
	static void dijkstra(const Graph  &G, const int &source, const int &destination, std::vector<int> &path);
public:
	static std::vector<Road> findShortestPath(MultiGraph<double, Station>* graph, Station* start, Station* end, double &lenght);
};


#endif // ALGORITHM_H
