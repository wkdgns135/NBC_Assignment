#pragma once
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author);
};