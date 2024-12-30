#include <iostream>
#include <algorithm>
using namespace std;


template<typename T>
class SimpleVector {
private:
	T* data = nullptr;
	int currentSize = 0;
	int currentCapacity = 0;

	void resize(int newCapacity) {
		if (currentCapacity >= newCapacity)return;
		T* temp = new T[newCapacity];
		for (int i = 0; i < currentSize; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		currentCapacity = newCapacity;
	}

public:
	SimpleVector(int capacity = 10){
		resize(capacity);
	}

	SimpleVector(const SimpleVector &other) : currentSize(other.currentSize), currentCapacity(other.currentCapacity) {
		data = new T[currentCapacity];
		for (int i = 0; i < currentSize; i++) {
			data[i] = other.data[i];
		}
	}

	~SimpleVector() {
		delete[] data;
	}

	T& operator [](unsigned int index) {
		if (index >= currentSize) {
			throw out_of_range("ÀÎµ¦½º°¡ ¹üÀ§¸¦ ¹þ¾î³µ½À´Ï´Ù.");
		}
		return data[index];
	}

	void push_back(const T &value) {
		if (currentSize == currentCapacity) {
			resize(currentCapacity + 5);
		}
		data[currentSize++] = value;
	}

	void pop_back() {
		if (currentSize == 0) {
			cout << "ºó ¹è¿­ÀÔ´Ï´Ù.\n";
			return;
		}
		currentSize--;
	}

	int size() {
		return currentSize;
	}

	int capacity() {
		return currentCapacity;
	}

	void sortData() {
		sort(data, data + currentSize);
	}
};

int main() {
	SimpleVector<int> sv(5);

	sv.push_back(3);
	sv.push_back(1);
	sv.push_back(4);
	sv.push_back(1);
	sv.push_back(5);
	sv.push_back(10);

	for (int i = 0; i < sv.size(); i++) {
		cout << sv[i] << " ";
	}
	cout << '\n';

	sv.sortData();

	for (int i = 0; i < sv.size(); i++) {
		cout << sv[i] << " ";
	}
	cout << '\n';

	sv.pop_back();
	sv.pop_back();

	for (int i = 0; i < sv.size(); i++) {
		cout << sv[i] << " ";
	}

	cout << '\n';
}