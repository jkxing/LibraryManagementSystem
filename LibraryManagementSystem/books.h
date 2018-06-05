#ifndef BOOKS_H
#define BOOKS_H
#include <string>
using namespace std;
class Book{
    std::string id;
    string name;
public:
    string getid();
    Book(std::string id);
};
#endif // BOOKS_H
