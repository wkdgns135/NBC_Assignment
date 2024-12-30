#include <iostream>
#include <string>
#include "Book.h"
#include "BorrowManager.h"
using namespace std;

int main() {
    BookManager bookManager;
    BorrowManager borrowManager(bookManager);

    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl;
        cout << "2. ��� å ���" << endl;
        cout << "3. å �뿩" << endl;
        cout << "4. å �ݳ�" << endl;
        cout << "5. ��ü ��� ���" << endl;
        cout << "6. ���� ��� ���" << endl;
        cout << "7. ���ں� ��� ���" << endl;
        cout << "8. ����" << endl;
        cout << "����: ";

        int choice;
        cin >> choice;
        string title, author;
        if (choice == 1) {
            cout << "å ����: ";
            cin.ignore();
            getline(cin, title);
            cout << "å ����: ";
            getline(cin, author);
            if (bookManager.addBook(title, author)) {
                borrowManager.initializeStock(bookManager.getBookByTitle(title));
            }
        }
        else if (choice == 2) {
            bookManager.displayAllBooks();
        }
        else if (choice == 3) {
            cout << "�뿩�� å ����: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.borrowBook(title);
        }
        else if (choice == 4) {
            cout << "�ݳ��� å ����: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.returnBook(title);
        }
        else if (choice == 5) {
            borrowManager.displayStock();
        }
        else if (choice == 6) {
            cout << "å �̸�: ";
            cin.ignore();
            getline(cin, title);
            borrowManager.displayStockByTitle(title);
        }
        else if (choice == 7) {
            cout << "���� �̸�: ";
            cin.ignore();
            getline(cin, author);
            borrowManager.displayStockByAuthor(author);
        }
        else if (choice == 8) {
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0;
}