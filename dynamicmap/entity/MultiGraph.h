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
		MultiGraph(DynamicArray<T>** matrix, DynamicArray<U>* vertex);
		bool addVertex(U vertex);
		bool addPathToVertex(U start, U end, T path);
		bool removePathFromVertex(U start, U end, T path);
		bool removeVertex(U vertex);

		DynamicArray<T>* findShortestPath();

		~MultiGraph();
	};

	template<class T, class U>
	MultiGraph<T, U> ::MultiGraph() : matrix(NULL), vertex(NULL)
	{
		
	}

	template<class T, class U>
	MultiGraph<T, U> ::MultiGraph(DynamicArray<T>** matrix, DynamicArray<U>* vertex)
	{
		
		this->matrix = matrix;
		this->vertex = vertex;
	}

	template<class T, class U>
	bool MultiGraph<T, U> ::addVertex(U vertex)
	{
		if (vertexs->addElem(vertex)) 
			return true;
		return false;

	}

	template<class T, class U>
	bool MultiGraph<T, U> ::addPathToVertex(U start, U end, T path)
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
	bool MultiGraph<T, U> ::removePathFromVertex(U start, U end, T path)
	{

		//TODO
		return false;
	}

	template<class T, class U>
	bool MultiGraph<T, U> ::removeVertex(U vertex)
	{
		//TODO
		return false;
	}

	template<class T, class U>
	MultiGraph<T, U> ::~MultiGraph()
	{

	}
}