#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "BookManager.h"

using namespace std;

class BorrowManager {
private:
    unordered_map<string, pair<int, int>> stock; // key : ����, value : {���� ���, �ִ� ���}
    BookManager* bookManager;

    bool hasStock(const string& title);
    void printStock(const string& title);

public:
    BorrowManager(BookManager& bookManager);
    void initializeStock(Book* book, int quantity = 3);
    void borrowBook(const string& title);
    void returnBook(const string& title);
    void displayStock();
    void displayStockByTitle(const string& title);
    void displayStockByAuthor(const string& author);
};