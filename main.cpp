#include <iostream>
#include <string>
#include "Book.h"
#include "BorrowManager.h"
using namespace std;

int main() {
    BookManager bookManager;
    BorrowManager borrowManager(bookManager);

    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl;
        cout << "2. 모든 책 출력" << endl;
        cout << "3. 책 대여" << endl;
        cout << "4. 책 반납" << endl;
        cout << "5. 전체 재고 출력" << endl;
        cout << "6. 제목별 재고 출력" << endl;
        cout << "7. 저자별 재고 출력" << endl;
        cout << "8. 종료" << endl;
        cout << "선택: ";

        int choice;
        cin >> choice;
        string title, author;
        if (choice == 1) {
            cout << "책 제목: ";
            cin.ignore();
            getline(cin, title);
            cout << "책 저자: ";
            getline(cin, author);
            if (bookManager.addBook(title, author)) {
                borrowManager.initializeStock(bookManager.getBookByTitle(title));
            }
        }
        else if (choice == 2) {
            bookManager.displayAllBooks();
        }
        else if (choice == 3) {
            cout << "대여할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.borrowBook(title);
        }
        else if (choice == 4) {
            cout << "반납할 책 제목: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 5) {
            borrowManager.displayStock();
        }
        else if (choice == 6) {
            cout << "책 이름: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.displayStockByTitle(title);
        }
        else if (choice == 7) {
            cout << "저자 이름: ";
            cin.ignore();
            getline(cin, author);
            borrowManager.displayStockByAuthor(author);
        }
        else if (choice == 8) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
    }

    return 0;
}