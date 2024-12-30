#pragma once
using namespace std;

template<typename T>
class SimpleVector {
private:
	T* data = nullptr;
	int currentSize = 0;
	int currentCapacity = 0;

	void resize(int newCapacity);

public:
	SimpleVector(int capacity = 10);

	SimpleVector(const SimpleVector& other);

	~SimpleVector();

	T& operator [](unsigned int index);

	void push_back(const T& value);
	void pop_back();
	int size();
	int capacity();
	void sortData();

};