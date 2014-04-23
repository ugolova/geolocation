#include "algorithm.h"



double Algorithm::findMin(DynamicArray<double> * arr)
{
	if (arr->getSize() > 0){
		double min = *arr->get(0);

		for (int i = 1; i < arr->getSize(); i++)
		{
			if (min > *arr->get(i))
				min = *arr->get(i);
		}
		return min;

	}
	return -1;
}
void Algorithm::dijkstra(const Graph  &G, const int &source, const int &destination, std::vector<int> &path)
{
	std::vector<float> d(G.size());
	std::vector<int> parent(G.size());
	for (unsigned int i = 0; i < G.size(); i++)
	{
		d[i] = std::numeric_limits<float>::max();
		parent[i] = -1;
	}
	std::priority_queue<std::pair<int, float>, std::vector<std::pair<int, float> >, Comparator> Q;
	d[source] = 0.0f;
	Q.push(std::make_pair(source, d[source]));
	while (!Q.empty())
	{
		int u = Q.top().first;
		if (u == destination) break;
		Q.pop();
		for (unsigned int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].first;
			float w = G[u][i].second;
			if (d[v] > d[u] + w)
			{
				d[v] = d[u] + w;
				parent[v] = u;
				Q.push(std::make_pair(v, d[v]));
			}
		}
	}
	path.clear();
	int p = destination;
	path.push_back(destination);
    while (p != source && p != -1)
	{
		p = parent[p];
		path.push_back(p);
	}
}
std::vector<Road> Algorithm::findShortestPath(MultiGraph<double, Station>* graph, Station* start, Station* end ,double &lenght)
{
	DynamicArray<Station> *stations = graph->getVertexs();
	std::vector<Road> result;
	if (stations->getIndex(start) != -1 && stations->getIndex(end) != -1)
	{
		DynamicArray<Station> *vertexs = graph->getVertexs();

		int size = vertexs->getSize();
		double* arr = new double[size*size];

		Graph g;
		g.resize(size);

		for (int i = 0; i < size; i++)
		{
			Station*startTemp= vertexs->get(i);
			for (int j = 0; j < size; j++)
			{
				Station*endTemp = vertexs->get(j);

				DynamicArray<double>* values = graph->getLenghtsByStation(startTemp, endTemp);
				if (values != 0 && values->getSize() > 0)
				{
					double value = Algorithm::findMin(values);
					arr[j*size + i] = value;
					g[i].push_back(std::make_pair(j, value));
				}
			}
		}
		std::vector<int> path;
		
		int startIndex = vertexs->getIndex(start);
		int endIndex = vertexs->getIndex(end);

		dijkstra(g, startIndex, endIndex, path);
		double sum = 0;
		for (int i = path.size() - 1; i >= 0; i--)
		{
			if (i - 1 >= 0)
			{
				Station * resultStart = vertexs->get(path[i]);
				Station * resultEnd = vertexs->get(path[i - 1]);
				Road road(resultStart, resultEnd);
				result.push_back(road);
				sum += arr[path[i - 1] * size + path[i]];
			}
			//std::cout << path[i] << "->";
		}
		//cout << "\n";
		//cout << sum;
		lenght = sum;
		delete[] arr;
	}
	
	return result;
}
