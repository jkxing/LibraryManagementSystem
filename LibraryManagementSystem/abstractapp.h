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
protected:
    vector<User*> users;
    vector<Book*> books;
    Database *db;
    enum registerState{
        Success,
        UserAlreadyExists,
        UserNameInvalid,
        PasswordInvalid
    };
#ifndef __Database
    map<string,string> userList;
#endif
public:
    enum loginState{
        SuccessLogin,
        WrongPassword,
        UserUnexist,
        Other
    };
    AbstractApp();
    virtual string getInput() = 0;
    virtual void ShowHelpPages() = 0;
    virtual void showMessage(const string &str) = 0;
    virtual void Register() = 0;
    virtual void exit() = 0;
    virtual string getLoginInfo() = 0;
    void borrowBook(User* user,Book* book);
    void returnBook(User* user,Book* book);
    vector<Book*> getBorrowedBook(User* user);
    vector<Book*> getReturnBook();
    void commitReturn(Book* book);
    void Login();
    void addBook();
    pair<loginState,string> verifyUser(const string &username,const string &password);
    vector<Book*> search(const map<string,string>& str);
    registerState addUser(const string &username,const string &password);
};
#endif // ABSTRACTAPP_H
