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
			throw out_of_range("�ε����� ������ ������ϴ�.");
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
			cout << "�� �迭�Դϴ�.\n";
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
    // �⺻ ������ �׽�Ʈ
    SimpleVector<int> sv1;
    cout << "�⺻ ������ �׽�Ʈ: capacity = " << sv1.capacity() << ", size = " << sv1.size() << endl;

    // ũ�⸦ �����ϴ� ������ �׽�Ʈ
    SimpleVector<int> sv2(5);
    cout << "ũ�⸦ �����ϴ� ������ �׽�Ʈ: capacity = " << sv2.capacity() << ", size = " << sv2.size() << endl;

    // push_back �׽�Ʈ
    sv2.push_back(3);
    sv2.push_back(1);
    sv2.push_back(4);
    sv2.push_back(1);
    sv2.push_back(5);
    sv2.push_back(10); // ũ�� �ʰ��� �迭 Ȯ��
    cout << "������ �߰� ��: ";
    for (int i = 0; i < sv2.size(); i++) {
        cout << sv2[i] << " ";
    }
    cout << "\ncapacity = " << sv2.capacity() << ", size = " << sv2.size() << endl;

    // pop_back �׽�Ʈ
    sv2.pop_back();
    sv2.pop_back();
    cout << "������ ���� ��: ";
    for (int i = 0; i < sv2.size(); i++) {
        cout << sv2[i] << " ";
    }
    cout << "\ncapacity = " << sv2.capacity() << ", size = " << sv2.size() << endl;

    // sortData �׽�Ʈ
    sv2.sortData();
    cout << "���� �� ������: ";
    for (int i = 0; i < sv2.size(); i++) {
        cout << sv2[i] << " ";
    }
    cout << endl;

    // ���� ������ �׽�Ʈ
    SimpleVector<int> sv3 = sv2; // ���� ������ ȣ��
    cout << "����� ������: ";
    for (int i = 0; i < sv3.size(); i++) {
        cout << sv3[i] << " ";
    }
    cout << "\ncapacity = " << sv3.capacity() << ", size = " << sv3.size() << endl;

    return 0;
}
