#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H

#include "dynamic_array.h"

namespace container {

	template<class T ,class U>
	class MultiGraph
	{
	private:
		
		DynamicArray<T>* matrix;
		DynamicArray<U>* vertexs;
        int capacity;
        int index;
        void increaseMatrix();
		

	public:
		MultiGraph();
		~MultiGraph();

        bool addVertex(U* vertex);
		void addPathToVertex(U* start, U* end, T* lenght);
		DynamicArray<T> * getLenghtsByStation(U* start, U* end);
		bool removePathFromVertex(U* start, U* end, T* lenght);
		bool removeVertex(U* vertex);
		DynamicArray<U>* getVertexs();

	};
}

    template<class T, class U>
    container::MultiGraph<T, U> ::MultiGraph():
        capacity(1),
        index(0)
    {
        vertexs = new DynamicArray<U>();
        matrix = new DynamicArray<T>[capacity*capacity];
    }

    template<class T, class U>
    void container::MultiGraph<T, U> ::increaseMatrix()
    {
        capacity = capacity * 2;
        DynamicArray<T> *temp = new DynamicArray<T>[capacity*capacity];
        for (int i = 0; i < index; i++)
        {
            for (int j = 0; j < index; j++)
            {
                temp[j*capacity + i] = matrix[j*capacity/2 + i];
            }
        }
        delete[] matrix;
        matrix = temp;
        temp = 0;
    }


    template<class T, class U>
    container::DynamicArray<T>* container::MultiGraph<T, U> ::getLenghtsByStation(U* start, U* end)
    {
        int i = vertexs->getIndex(start);
        int j = vertexs->getIndex(end);
        if (i != -1 && j != -1)
            return &matrix[j*capacity + i];
        return 0;
    }

    template<class T, class U>
    bool container::MultiGraph<T, U> ::addVertex(U* vertex)
    {
        if (vertexs->addElem(vertex)){
            if (index == capacity)
                increaseMatrix();
            index++;
            return true;
        }
        return false;
    }
    template<class T, class U>
    container::DynamicArray<U>* container::MultiGraph<T, U> ::getVertexs()
    {
        return vertexs;
    }

    template<class T, class U>
    void container::MultiGraph<T, U> ::addPathToVertex(U* start, U* end, T* lenght)
    {
        int i = vertexs->getIndex(start);
        if (i == -1)
        {
            addVertex(start);
            i = vertexs->getIndex(start);
        }

        int j = vertexs->getIndex(end);
        if (j == -1)
        {
            addVertex(end);
            j = vertexs->getIndex(end);
        }
        DynamicArray<T>* temp = &matrix[j*capacity + i];
        temp->addElem(lenght);

    }

    template<class T, class U>
    bool container::MultiGraph<T, U> ::removePathFromVertex(U* start, U* end, T* lenght)
    {
        int i = vertexs->getIndex(start);
        int j = vertexs->getIndex(end);
        if (i != -1 && j != -1)
        {
            DynamicArray<T> * tempArr = &matrix[j*capacity + i];

            if (tempArr->removeElem(tempArr->getIndex(lenght)) != -1)
            {
                tempArr = 0;
                return true;
            }
            else
            {
                false;
            }
        }
        else
        {
            return false;
        }

    }

    template<class T, class U>
    bool container::MultiGraph<T, U> ::removeVertex(U* vertex)
    {
        int key = vertexs->getIndex(vertex);
        if (key != -1)
        {
            DynamicArray<T> *tempMatrix = new DynamicArray<T>[capacity*capacity];
            for (int i = 0 ,k = 0 ; i < index; i++)
            {
                for (int j = 0 , l = 0; j < index; j++)
                {
                    if (i == key || j == key)
                        continue;

                    tempMatrix[l*capacity + k] = matrix[j*capacity + i];
                    l++;
                }
                if (i != key)
                    k++;
            }
            delete[] matrix;

            vertexs->removeElem(key);
            index--;

            matrix = tempMatrix;
            tempMatrix = 0;
        }
        else
        {
            return false;
        }

    }

    template<class T, class U>
    container::MultiGraph<T, U> ::~MultiGraph()
    {

    }

#endif // MULTIGRAPH_H
