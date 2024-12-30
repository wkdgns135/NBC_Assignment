#include "BorrowManager.h"

BorrowManager::BorrowManager(BookManager& bookManager) : bookManager(&bookManager) {};

bool BorrowManager::hasStock(const string& title) {
    return stock.find(title) != stock.end() && stock.at(title).first > 0;
}

void BorrowManager::printStock(const string& title) {
    if (stock.find(title) != stock.end()) {
        cout << "책 이름: " << title << ", 재고: " << stock.at(title).first << endl;
    }
    else {
        cout << "책 [" << title << "]는 재고 정보가 없습니다." << endl;
    }
}

void BorrowManager::initializeStock(Book* book, int quantity) {
    stock[book->title] = { quantity ,quantity };
}

void BorrowManager::borrowBook(const string& title) {
    if (hasStock(title)) {
        cout << title << "책을 대여하셨습니다." << endl;
        printStock(title);
        stock[title].first--;
    }
    else {
        cout << "해당 책의 재고가 없습니다." << endl;
    }
}

void BorrowManager::returnBook(const string& title) {
    if (stock.find(title) != stock.end()) {
        if (stock[title].first < stock[title].second) {
            stock[title].first++;
            cout << title << " 책을 반납하셨습니다." << endl;
            printStock(title);
        }
        else {
            cout << "반납 불가능: 재고가 이미 최대입니다." << endl;
        }
    }
    else {
        cout << "존재하지 않는 책입니다." << endl;
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
    cout << "저자 : " << author << "의 책 목록 입니다." << endl;
    for (auto& book : bookManager->getBooksByAuthor(author)) {
        printStock(book->title);
    }
}
