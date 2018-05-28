#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using namespace std;
class Database{
    static mongocxx::instance inst;
    static mongocxx::client conn;
    mongocxx::collection borrowCollection;
    mongocxx::collection returnCollection;
    mongocxx::collection userCollection;
    mongocxx::collection bookCollection;
public:
    Database();
    bool existUser(const string &username);
    void addBook(const map<string,string> &bookInfo);
    void addUser(const string &user_id,const string &password);
    void newBorrow(const string &user_id,const string &book_id);
    void addReturn(const string &user_id,const string &book_id);
    vector<string> getBorrowedList(const string &user_id);
    vector<string> getReturnList();
    pair<string,string> getUserPassword(const string &username);
    void commitReturn(const string &book_id);
    vector<string> search(const map<string,string>& keyword);
};
#endif // DATABASE_H
