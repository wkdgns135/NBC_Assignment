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

// å �߰� �޼���
bool BookManager::addBook(const string& title, const string& author) {
    if (findBookByTitle(title) != nullptr) {
        cout << "�̹� �����ϴ� ������ å�Դϴ�." << endl;
        return false;
    }
    books.push_back(Book(title, author)); // push_back ���
    cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    return true;
}

// ��� å ��� �޼���
void BookManager::displayAllBooks(){
    if (books.empty()) {
        cout << "���� ��ϵ� å�� �����ϴ�." << endl;
        return;
    }

    cout << "���� ���� ���:" << endl;
    for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
        cout << "- " << books[i].title << " by " << books[i].author << endl;
    }
}

Book* BookManager::getBookByTitle(const string& title) {
    return findBookByTitle(title);
}

vector<Book*> BookManager::getBooksByAuthor(const string& author) {
    return findBooksByAuthor(author);
}
