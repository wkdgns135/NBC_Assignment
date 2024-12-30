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
			throw out_of_range("인덱스가 범위를 벗어났습니다.");
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
			cout << "빈 배열입니다.\n";
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
    // 기본 생성자 테스트
    SimpleVector<int> sv1;
    cout << "기본 생성자 테스트: capacity = " << sv1.capacity() << ", size = " << sv1.size() << endl;

    // 크기를 지정하는 생성자 테스트
    SimpleVector<int> sv2(5);
    cout << "크기를 지정하는 생성자 테스트: capacity = " << sv2.capacity() << ", size = " << sv2.size() << endl;

    // push_back 테스트
    sv2.push_back(3);
    sv2.push_back(1);
    sv2.push_back(4);
    sv2.push_back(1);
    sv2.push_back(5);
    sv2.push_back(10); // 크기 초과로 배열 확장
    cout << "데이터 추가 후: ";
    for (int i = 0; i < sv2.size(); i++) {
        cout << sv2[i] << " ";
    }
    cout << "\ncapacity = " << sv2.capacity() << ", size = " << sv2.size() << endl;

    // pop_back 테스트
    sv2.pop_back();
    sv2.pop_back();
    cout << "데이터 제거 후: ";
    for (int i = 0; i < sv2.size(); i++) {
        cout << sv2[i] << " ";
    }
    cout << "\ncapacity = " << sv2.capacity() << ", size = " << sv2.size() << endl;

    // sortData 테스트
    sv2.sortData();
    cout << "정렬 후 데이터: ";
    for (int i = 0; i < sv2.size(); i++) {
        cout << sv2[i] << " ";
    }
    cout << endl;

    // 복사 생성자 테스트
    SimpleVector<int> sv3 = sv2; // 복사 생성자 호출
    cout << "복사된 데이터: ";
    for (int i = 0; i < sv3.size(); i++) {
        cout << sv3[i] << " ";
    }
    cout << "\ncapacity = " << sv3.capacity() << ", size = " << sv3.size() << endl;

    return 0;
}
