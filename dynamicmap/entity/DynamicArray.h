#pragma once


namespace dynamicMap{

	template<class T>
	class DynamicArray
	{

	private:
		
		int capacity ;
		int index ;
		T* arr;
		
		void increaseSize(int newCapicity);

	public:
		DynamicArray();
		bool addElem(T elem);
		bool removeElem(int num);
		void printArray();
		int getIndex(T elem);
		bool contains(T elem);



		int getSize();
		~DynamicArray();
	};

	template<class T> DynamicArray<T>::DynamicArray() :capacity(8), index(0), arr(NULL)
	{
	
	}

	template<class T> int DynamicArray<T>::getSize()
	{
		return index;
	}
	

	template<class T> bool DynamicArray<T>::addElem(T elem)
	{
		if (elem == NULL)
			return false;

		if (index == capacity)
		{
			increaseSize(capacity * 2);
		}
	
		arr[index] = elem;
		index++;
		return true;
	}

	template<class T> bool DynamicArray<T>::removeElem(int num)
	{
		
		if (num > index || num < 0){
			return false;
		}

		T* result = new T[index - 1];
	
		for (int i = 0, j = 0; j < index -1 ; i++)
		{
			if (i == num)
				continue;
			result[j] = arr[i];
			j++;
		}
		delete[] arr;
	    arr = result;
	
		index--;
		return true;

	}

	template<class T> int DynamicArray<T>::getIndex(T elem)
	{
		if (elem == NULL)
			return -1;

		for (int i = 0; i < index; i++)
		{
			if (arr[i] == elem)
				return i;
		}
		return -1;
	}

	template<class T> bool DynamicArray<T>::contains(T elem)
	{
		if (elem == NULL)
			return false;
		if (getIndex(elem) != -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T> void DynamicArray<T>::increaseSize(int newCapicity)
	{
		T * temp = new T[newCapicity];
		for (int i = 0; i < capacity; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		capacity = newCapicity;
	}



	template<class T> void DynamicArray<T>::printArray()
	{
		for (int i = 0; i < index; i++)
		{
			std:: cout << arr[i] << "\n";
		}
	}


	template<class T> DynamicArray<T>::~DynamicArray()
	{
		
	}
}


