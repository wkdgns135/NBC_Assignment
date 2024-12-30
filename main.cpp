#include <iostream>
#include "SimpleVector.h"
using namespace std;

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
