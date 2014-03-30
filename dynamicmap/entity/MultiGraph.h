#pragma once
#include "DynamicArray.h"

namespace dynamicMap{

	template<class T ,class U>
	class MultiGraph
	{
	private:

		DynamicArray<T>** matrix;
		DynamicArray<U>* vertex;
		void initMatrix(int xSize, int ySize);

	public:
		MultiGraph();

		bool addVertext(U* vertex);
		bool addPathsToVertex(U* start, U* end, T* path);
		bool removePathsFromVertex(U* start, U* end, T* path);

		DynamicArray<T>* findShortestPath();

		~MultiGraph();
	};

	template<class T, class U>
	MultiGraph<T, U> ::MultiGraph() : matrix(NULL), vertex(NULL)
	{
		
	}

	template<class T, class U>
	bool MultiGraph<T, U> ::addVertext(U* vertex)
	{
		if (vertexs->addElem(vertex)) 
			return true;
		return false;

	}

	template<class T, class U>
	bool MultiGraph<T, U> ::addPathsToVertex(U* start, U* end, T* path)
	{
		if (path == NULL)
			return false;

		int i ,j= 0;
		if ((i = vertexs->getIndex(start)) != -1 && (j = vertexs->getIndex(end)) != -1)
		{
			//TODO
		}

		return false;
	}

	template<class T, class U>
	bool MultiGraph<T, U> ::removePathsFromVertex(U* start, U* end, T* path)
	{

		//TODO
		return false;
	}
		

	template<class T, class U>
	MultiGraph<T, U> ::~MultiGraph()
	{

	}
	
}