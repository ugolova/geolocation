#pragma once
#include "DynamicArray.h"

namespace dynamicMap{

	template<class T ,class U>
	class MultiGraph
	{
	private:

		DynamicArray<T>* matrix;
		DynamicArray<U>* vertexs;
		int capacity = 1;
		int index = 0;

		void increaseMatrix();
		bool addVertex(U* vertex);

	public:
		MultiGraph();
		~MultiGraph();
		
		bool addPathToVertex(U* start, U* end, T* path);
		bool removePathFromVertex(U start, U end, T path);
		bool removeVertex(U vertex);
		DynamicArray<T>* findShortestPath();
		
		

	};

	template<class T, class U>
	MultiGraph<T, U> ::MultiGraph()
	{
		vertexs = new DynamicArray<U>();
		matrix = new DynamicArray<T>[capacity*capacity];
	}

	template<class T, class U>
	void MultiGraph<T, U> ::increaseMatrix()
	{
		capacity = capacity * 2;
		DynamicArray<T> *temp = new DynamicArray<T>[capacity*capacity];
		for (int i = 0; i < index; i++)
		{
			for (int j = 0; j < index; j++)
			{
				temp[j*index + i] = matrix[j*index + i];
			}
		}
		delete[] matrix;
		matrix = temp;
	}


	template<class T, class U>
	bool MultiGraph<T, U> ::addVertex(U* vertex)
	{
		if (vertexs->addElem(vertex)){
			index++;
			return true;
		}
		
		return false;
	}

	
	template<class T, class U>
	bool MultiGraph<T, U> ::addPathToVertex(U* start, U* end, T* path)
	{
		if (path != NULL)
		{

			//TODO
			int i, j = 0;
			if ((i = vertexs->getIndex(start)) != -1 && (j = vertexs->getIndex(end)) != -1)
			{
				if (index == capacity);
					increaseMatrix();
				vertexs->addElem(start);
				vertexs->addElem(end);
				
				i = vertexs->getIndex(start);
				j = vertexs->getIndex(end);
				
				//matrix[j*capacity + i] = path;
			}
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