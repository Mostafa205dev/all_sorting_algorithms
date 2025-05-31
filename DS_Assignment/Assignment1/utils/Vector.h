#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Vector
{
	int capacity;
	int size;
	T *arr;

public:
	Vector(int s);
	Vector();
	~Vector(); // Destructor to free memory
	void push(T t);
	void pop_back();
	void removeAt(int index);
	void sort();
	T back();
	T front();
	int get_size();
	int get_capacity();
	void swap(int ind1, int ind2);
	void print();
	void clear();

	T &operator[](int index) const;

	Vector(const Vector &other) : size(other.size), capacity(other.capacity)
	{
		if (size > 0)
		{
			arr = new T[size];
			for (size_t i = 0; i < size; ++i)
				arr[i] = other.arr[i];
		}
		else
		{
			arr = nullptr;
		}
	}

	void operator=(const Vector<T> &vec)
	{
		delete[] arr;
		size = vec.size;
		capacity = vec.capacity;
		if (size == 0)
		{
			arr = nullptr;
			return;
		}
		arr = new T[size];

		for (int i = 0; i < size; i++)
		{
			arr[i] = vec[i];
		}
	}
};

template <typename T>
Vector<T>::Vector(int s) : capacity(s), size(s)
{
	arr = new T[s];
	for (int i = 0; i < s; i++)
	{
		arr[i] = 0;
	}
}

template <typename T>
Vector<T>::Vector() : capacity(0), size(0), arr(nullptr)
{
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] arr;
}

template <typename T>
void Vector<T>::pop_back()
{
	if (size > 0)
		size--;
}

template <typename T>
void Vector<T>::clear()
{
	size = 0;
}

template <typename T>
void Vector<T>::push(T t)
{
	if (size == capacity)
	{
		if (capacity == 0)
			capacity = 1;
		capacity *= 2;
		T *temp = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
	arr[size] = t;
	size++;
}

template <typename T>
void Vector<T>::removeAt(int index)
{
	if (index < 0 || index >= size)
		return; // Add bounds check
	size--;
	for (int i = index; i < size; i++)
	{
		arr[i] = arr[i + 1];
	}
}

template <typename T>
T Vector<T>::back()
{
	if (size > 0)
		return arr[size - 1]; // Return the last element
	throw std::out_of_range("Vector is empty");
}

template <typename T>
T Vector<T>::front()
{
	if (size > 0)
		return arr[0]; // Return the first element
	throw std::out_of_range("Vector is empty");
}

template <typename T>
void Vector<T>::sort()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i] > arr[j])
			{
				T temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

template <typename T>
int Vector<T>::get_size()
{
	return size;
}

template <typename T>
int Vector<T>::get_capacity()
{
	return capacity;
}

template <typename T>
T &Vector<T>::operator[](int index) const
{
	if (index < 0 || index >= size)
	{
		cout << size << endl;
		cout << index << endl;
		throw std::out_of_range("Index out of range");
	}
	return arr[index];
}

template <typename T>
void Vector<T>::swap(int ind1, int ind2)
{
	if (ind1 < 0 || ind2 < 0 || ind1 >= size || ind2 >= size)
		return; // Add bounds check
	T temp = arr[ind1];
	arr[ind1] = arr[ind2];
	arr[ind2] = temp;
}

template <typename T>
void Vector<T>::print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
