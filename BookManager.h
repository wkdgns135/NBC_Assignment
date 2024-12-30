#pragma once
#include <vector>
#include <string>
#include "Book.h"

using namespace std;

class BookManager {
private:
    vector<Book> books; // 책 목록 저장
    Book* findBookByTitle(const string& title);
    vector<Book*> findBooksByAuthor(const string& author);
public:
    bool addBook(const string& title, const string& author); // 책 추가 메서드
    void displayAllBooks(); // 모든 책 출력 메서드
    Book* getBookByTitle(const string& title);
    vector<Book*> getBooksByAuthor(const string& author);
};