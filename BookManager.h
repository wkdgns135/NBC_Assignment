#pragma once
#include <vector>
#include <string>
#include "Book.h"

using namespace std;

class BookManager {
private:
    vector<Book> books; // å ��� ����
    Book* findBookByTitle(const string& title);
    vector<Book*> findBooksByAuthor(const string& author);
public:
    bool addBook(const string& title, const string& author); // å �߰� �޼���
    void displayAllBooks(); // ��� å ��� �޼���
    Book* getBookByTitle(const string& title);
    vector<Book*> getBooksByAuthor(const string& author);
};