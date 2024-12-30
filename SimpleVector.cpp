#include <iostream>
#include <algorithm>
#include "SimpleVector.h"

template <typename T>
void SimpleVector<T>::resize(int newCapacity) {
	if (currentCapacity >= newCapacity)return;
	T* temp = new T[newCapacity];
	for (int i = 0; i < currentSize; i++) {
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	currentCapacity = newCapacity;
}

template <typename T>
SimpleVector<T>::SimpleVector(int capacity) {
	resize(capacity);
}

template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector& other) : currentSize(other.currentSize), currentCapacity(other.currentCapacity){
	data = new T[currentCapacity];
	for (int i = 0; i < currentSize; i++) {
		data[i] = other.data[i];
	}
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
	delete[] data;
}

template <typename T>
T& SimpleVector<T>:: operator [](unsigned int index) {
	if (index >= currentSize) {
		throw out_of_range("ÀÎµ¦½º°¡ ¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.");
	}
	return data[index];
}

template <typename T>
void SimpleVector<T>::push_back(const T& value) {
	if (currentSize == currentCapacity) {
		resize(currentCapacity + 5);
	}
	data[currentSize++] = value;
}

template <typename T>
void SimpleVector<T>::pop_back() {
	if (currentSize == 0) {
		cout << "ºó ¹è¿­ÀÔ´Ï´Ù.\n";
		return;
	}
	currentSize--;
}

template <typename T>
int SimpleVector<T>::size() {
	return currentSize;
}

template <typename T>
int SimpleVector<T>::capacity() {
	return currentCapacity;
}

template <typename T>
void SimpleVector<T>::sortData() {
	sort(data, data + currentSize);
}

template class SimpleVector<int>;