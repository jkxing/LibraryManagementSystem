#ifndef ABSTRACTAPP_H
#define ABSTRACTAPP_H
#include <books.h>
#include <database.h>
#include <user.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;
class AbstractApp{
public:
    AbstractApp();
    virtual void main() = 0;
    virtual string getInput() = 0;
    virtual void ShowHelpPages() = 0;
    virtual void showMessage(const string &str) = 0;
    virtual void exit() = 0;
    virtual ~AbstractApp();

    /*void borrowBook(User* user,Book* book);
    void returnBook(User* user,Book* book);
    vector<Book*> getBorrowedBook(User* user);
    vector<Book*> getReturnBook();
    void commitReturn(Book* book);
    void addBook();
    map<string,string> getUserInfo(User* user,const vector<string>& key);
    void updateUserInfo(User* user,const map<string,string>& info);
    map<string,string> getBookInfo(Book* user,const vector<string>& key);
    void updateBookInfo(Book* user,const map<string,string>& info);
    vector<Book*> search(const map<string,string>& str);
    registerState addUser(const string &username,const string &password);*/
};
#endif // ABSTRACTAPP_H
