#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

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
		bool addElem(T* elem);
		bool removeElem(int num);
		void printArray();
		T* get(int num);
		int getIndex(T* elem);
		bool contains(T* elem);
	
		int getSize();
		~DynamicArray();
	};


    template<class T> DynamicArray<T>::DynamicArray() :capacity(1), index(0), arr(0)
    {

    }

    template<class T> int DynamicArray<T>::getSize()
    {
        return index;
    }

    template<class T> bool DynamicArray<T>::addElem(T* elem)
    {
        if (elem != 0)
        {
            if (index == 0)
                arr = new T[capacity];
            if (index == capacity)
                increaseSize(capacity * 2);
            arr[index] = *elem;
            index++;
        }
        return true;
    }


    template<class T> T* DynamicArray<T>::get(int num)
    {
        if (num > index || num < 0)
            return 0;
        for (int i = 0; i < index; i++)
        {
            if (i == num)
                return &arr[i];
        }
        return 0;

    }

    template<class T> bool DynamicArray<T>::removeElem(int num)
    {

        if (num > index || num < 0)
            return false;

        T* result = new T[capacity];
        for (int i = 0, j = 0; j < index -1 ; i++)
        {
            if (i == num)
                continue;
            result[j] = arr[i];
            j++;
        }
        delete[] arr;
        arr = 0;
        arr = result;

        result = 0;

        index--;
        return true;

    }

    template<class T> int DynamicArray<T>::getIndex(T* elem)
    {
        if (elem != 0)
        {
            for (int i = 0; i < index; i++)
            {
                if (arr[i] == *elem)
                    return i;
            }
        }
        return -1;
    }

    template<class T> bool DynamicArray<T>::contains(T* elem)
    {
        if (elem != 0)
        {
            if (getIndex(elem) != -1)
            {
                return true;
            }
        }
        return false;
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
        temp = 0;
        capacity = newCapicity;
    }


    template<class T> DynamicArray<T>::~DynamicArray()
    {

    }

#endif // DYNAMICARRAY_H
