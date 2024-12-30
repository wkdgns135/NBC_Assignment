#include <iostream>
#include "SimpleVector.h"
using namespace std;

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
