#include "BorrowManager.h"

BorrowManager::BorrowManager(BookManager& bookManager) : bookManager(&bookManager) {};

bool BorrowManager::hasStock(const string& title) {
    return stock.find(title) != stock.end() && stock.at(title).first > 0;
}

void BorrowManager::printStock(const string& title) {
    if (stock.find(title) != stock.end()) {
        cout << "å �̸�: " << title << ", ���: " << stock.at(title).first << endl;
    }
    else {
        cout << "å [" << title << "]�� ��� ������ �����ϴ�." << endl;
    }
}

void BorrowManager::initializeStock(Book* book, int quantity) {
    stock[book->title] = { quantity ,quantity };
}

void BorrowManager::borrowBook(const string& title) {
    if (hasStock(title)) {
        cout << title << "å�� �뿩�ϼ̽��ϴ�." << endl;
        printStock(title);
        stock[title].first--;
    }
    else {
        cout << "�ش� å�� ��� �����ϴ�." << endl;
    }
}

void BorrowManager::returnBook(const string& title) {
    if (stock.find(title) != stock.end()) {
        if (stock[title].first < stock[title].second) {
            stock[title].first++;
            cout << title << " å�� �ݳ��ϼ̽��ϴ�." << endl;
            printStock(title);
        }
        else {
            cout << "�ݳ� �Ұ���: ��� �̹� �ִ��Դϴ�." << endl;
        }
    }
    else {
        cout << "�������� �ʴ� å�Դϴ�." << endl;
    }
}

void BorrowManager::displayStock() {
    for (auto& book : stock) {
        printStock(book.first);
    }
}

void BorrowManager::displayStockByTitle(const string& title) {
    printStock(title);
}

void BorrowManager::displayStockByAuthor(const string& author) {
    cout << "���� : " << author << "�� å ��� �Դϴ�." << endl;
    for (auto& book : bookManager->getBooksByAuthor(author)) {
        printStock(book->title);
    }
}
