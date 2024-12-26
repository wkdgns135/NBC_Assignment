#include <iostream>
#include <queue>
using namespace std;

class Array {
	int type; // 0 : Asc, 1 : Desc
	int size; 
	int *arr;
	
	bool Compare(int a, int b) {
		return type ? a > b : a < b;
	}

	int Calc_Sum() {
		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += arr[i];
		}
		return sum;
	}

	float Calc_Avg() {
		return (float)Calc_Sum() / size;
	}

	void Insertion_Sort() {
		for (int i = 1; i < size; i++) {
			int key = arr[i];
			int j = i - 1;
			for (j; j >= 0 && Compare(key , arr[j]); j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = key;
		}
	}

	void Heap_Sort(int left, int right) {
		priority_queue<int> pq;
		for (int i = left; i < right; i++) {
			pq.push(arr[i]);
		}
		for (int i = left; i < right; i++) {
			arr[i] = pq.top();
			pq.pop();
		}
	}

	void Quick_Sort(int left, int right, int depth) {
		if (depth == 0) {
			int size = right - left + 1;
			if (size > 16) Heap_Sort(left, right);
			return;
		}
		int i = left, j = right;
		int pivot = arr[(left + right) / 2];
		int temp;

		do {
			for (; Compare(arr[i] , pivot); i++);
			for (; !Compare(arr[j] , pivot); j--);
			if (i <= j) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				i++, j--;
			}
		} while (i <= j);

		if (left < j)Quick_Sort(left, j, depth - 1);
		if (i < right)Quick_Sort(i, right, depth - 1);
	}

public:
	Array() {
		while (1) {
			cout << "�迭�� ũ�⸦ �Է����ּ��� : ";
			cin >> size;
			if (size > 0 && size < INT_MAX)break;
			cout << "�߸��� �Է��Դϴ�.\n";
		}

		while (1) {
			cout << "��������, ���������� �������ּ��� (1: ��������, 2: ��������) : ";
			cin >> type;
			if (type == 1 || type == 2)break;
			cout << "�߸��� �Է��Դϴ�.\n";
		}
		type--;
		this->arr = new int[size];

		cout << "�迭 " << size << "�ڸ��� �Է����ּ���.\n";
		for (int i = 0; i < size; i++) cin >> arr[i];
	}

	~Array(){
		delete[] arr;
	}


	void Sort() {
		if (size <= 16) {
			Insertion_Sort();
			return;
		}
		Quick_Sort(0, size - 1, 2 * ceil(log2(size)));
		Insertion_Sort();
	}

	void Print_Sum() {
		cout << Calc_Sum() << '\n';
	}
	void Print_Avg() {
		cout << Calc_Avg() << '\n';
	}
	void Print_Array() {
		for (int i = 0; i < size; i++)cout << arr[i] << ' ';
		cout << '\n';
	}
};


int main() {
	Array array;
	cout << "���� : ";
	array.Print_Sum();
	cout << "��� : ";
	array.Print_Avg();
	cout << "�迭 ���� ��� : ";
	array.Print_Array();
	
	array.Sort();
	cout << "���� �Ϸ�.\n";
	cout << "�迭 ���� ��� : ";
	array.Print_Array();

}