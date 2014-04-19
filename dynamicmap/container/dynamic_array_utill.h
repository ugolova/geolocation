#ifndef DYNAMIC_ARRAY_UTIL_H
#define DYNAMIC_ARRAY_UTIL_H

#include "dynamic_array.h"

template<class T>
class DynamicArrayUtill
{
public:
	static T findMin(DynamicArray<T>* arr);
};


template<class T>
T DynamicArrayUtill<T>::findMin(DynamicArray<T>* arr)
{
	int size = arr->getSize();

	if (size > 0)
	{
		T min = *arr->get(0);
		for (int i = 1; i < size; i++)
		{
			T temp = *arr->get(i);

			if (min > *arr->get(i))
				min = *arr->get(i);
		}
		return min;
	}
	T* abc = new T();
	return *abc;
	
}


#endif // DYNAMIC_ARRAY_UTIL_H
