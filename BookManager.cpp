#include <iostream>
#include "BookManager.h"

Book* BookManager::findBookByTitle(const string& title) {
    for (auto& book : books) {
        if (book.title == title)return &book;
    }
    return nullptr;
}
vector<Book*> BookManager::findBooksByAuthor(const string& author) {
    vector<Book*> temp;
    for (auto& book : books) {
        if (book.author == author)temp.push_back(&book);
    }
    return temp;
}

// 책 추가 메서드
bool BookManager::addBook(const string& title, const string& author) {
    if (findBookByTitle(title) != nullptr) {
        cout << "이미 존재하는 제목의 책입니다." << endl;
        return false;
    }
    books.push_back(Book(title, author)); // push_back 사용
    cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    return true;
}

// 모든 책 출력 메서드
void BookManager::displayAllBooks(){
    if (books.empty()) {
        cout << "현재 등록된 책이 없습니다." << endl;
        return;
    }

    cout << "현재 도서 목록:" << endl;
    for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
        cout << "- " << books[i].title << " by " << books[i].author << endl;
    }
}

Book* BookManager::getBookByTitle(const string& title) {
    return findBookByTitle(title);
}

vector<Book*> BookManager::getBooksByAuthor(const string& author) {
    return findBooksByAuthor(author);
}
