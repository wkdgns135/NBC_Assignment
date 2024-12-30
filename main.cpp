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
    vector<Book> books; // å ��� ����
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
    // å �߰� �޼���
    bool addBook(const string& title, const string& author) {
        if (findBookByTitle(title) != nullptr) {
            cout << "�̹� �����ϴ� ������ å�Դϴ�." << endl;
            return false;
        }
        books.push_back(Book(title, author)); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
        return true;
    }

    // ��� å ��� �޼���
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
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
    unordered_map<string, pair<int,int>> stock; // key : ����, value : {���� ���, �ִ� ���}
    BookManager *bookManager;

    bool hasStock(const string& title) const {
        return stock.find(title) != stock.end() && stock.at(title).first > 0;
    }

    void printStock(const string& title) const {
        if (stock.find(title) != stock.end()) {
            cout << "å �̸�: " << title << ", ���: " << stock.at(title).first << endl;
        }
        else {
            cout << "å [" << title << "]�� ��� ������ �����ϴ�." << endl;
        }
    }

public:
    BorrowManager(BookManager &bookManager) : bookManager(&bookManager) {};

    void initializeStock(Book *book, int quantity = 3) {
        stock[book->title] = { quantity ,quantity };
    }

    void borrowBook(const string &title) {
        if (hasStock(title)) {
            cout << title << "å�� �뿩�ϼ̽��ϴ�." << endl;
            printStock(title);
            stock[title].first--;
        }
        else {
            cout << "�ش� å�� ��� �����ϴ�." << endl;
        }
    }

    void returnBook(const string& title) {
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

    void displayStock() {
        for (auto& book : stock) {
            printStock(book.first);
        }
    }

    void displayStockByTitle(const string& title) {
        printStock(title);
    }

    void displayStockByAuthor(const string &author) {
        cout << "���� : " << author << "�� å ��� �Դϴ�." << endl;
        for (auto& book : bookManager->getBooksByAuthor(author)) {
            printStock(book->title);
        }
    }
};

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