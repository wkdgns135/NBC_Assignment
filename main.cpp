#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장
    Book* findBookByTitle(const string &title) {
        for (auto& book : books) {
            if (book.title == title)return &book;
        }
        return nullptr;
    }
    vector<Book*> findBooksByAuthor(const string & author) {
        vector<Book*> temp;
        for (auto& book : books) {
            if (book.author == author)temp.push_back(&book);
        }
        return temp;
    }
public:
    // 책 추가 메서드
    bool addBook(const string& title, const string& author) {
        if (findBookByTitle(title) != nullptr) {
            cout << "이미 존재하는 제목의 책입니다." << endl;
            return false;
        }
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
        return true;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    Book* getBookByTitle(const string &title) {
        return findBookByTitle(title);
    }

    vector<Book*> getBooksByAuthor(const string &author) {
        return findBooksByAuthor(author);
    }
};

class BorrowManager {
private:
    unordered_map<string, pair<int,int>> stock; // key : 제목, value : {현재 재고, 최대 재고}
    BookManager *bookManager;

    bool hasStock(const string& title) const {
        return stock.find(title) != stock.end() && stock.at(title).first > 0;
    }

    void printStock(const string& title) const {
        if (stock.find(title) != stock.end()) {
            cout << "책 이름: " << title << ", 재고: " << stock.at(title).first << endl;
        }
        else {
            cout << "책 [" << title << "]는 재고 정보가 없습니다." << endl;
        }
    }

public:
    BorrowManager(BookManager &bookManager) : bookManager(&bookManager) {};

    void initializeStock(Book *book, int quantity = 3) {
        stock[book->title] = { quantity ,quantity };
    }

    void borrowBook(const string &title) {
        if (hasStock(title)) {
            cout << title << "책을 대여하셨습니다." << endl;
            printStock(title);
            stock[title].first--;
        }
        else {
            cout << "해당 책의 재고가 없습니다." << endl;
        }
    }

    void returnBook(const string& title) {
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

    void displayStock() {
        for (auto& book : stock) {
            printStock(book.first);
        }
    }

    void displayStockByTitle(const string& title) {
        printStock(title);
    }

    void displayStockByAuthor(const string &author) {
        cout << "저자 : " << author << "의 책 목록 입니다." << endl;
        for (auto& book : bookManager->getBooksByAuthor(author)) {
            printStock(book->title);
        }
    }
};

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