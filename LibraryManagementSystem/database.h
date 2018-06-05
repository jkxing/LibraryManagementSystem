#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <map>
using namespace  std;
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/cursor.hpp>
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using namespace std;
class Database{
    mongocxx::pool pool;
    std::queue<thread*> threads;
    //static mongocxx::client conn;
    //mongocxx::collection borrowCollection;
    //mongocxx::collection returnCollection;
    //mongocxx::collection userCollection;
    //mongocxx::collection bookCollection;
public:
    Database();
    ~Database();
    void sync();
    /*void addBook(const map<string,string> &bookInfo);
    void newBorrow(const string &user_id,const string &book_id);
    void addReturn(const string &user_id,const string &book_id);
    vector<string> getBorrowedList(const string &user_id);
    vector<string> getReturnList();

    void commitReturn(const string &book_id);
    vector<string> search(const map<string,string>& keyword);
    map<string,string> getUserInfo(const string &user_id,const vector<string> &key);
    void updateUserInfo(const string &user_id,const map<string,string>& info);
    map<string,string> getBookInfo(const string &book_id,const vector<string> &key);
    void updateBookInfo(const string &book_id,const map<string,string>& info);*/
    bsoncxx::document::value get(const string &str,bsoncxx::document::value key);
    mongocxx::cursor getAll(const string &str,bsoncxx::document::value key);
    bool insert(const string &str,bsoncxx::document::value item);
    bool update(const string &str,bsoncxx::document::value oldItem,bsoncxx::document::value newItem);
    bool remove(const string &str,bsoncxx::document::value item);
    bool find(const string &str,bsoncxx::document::value key);
};
#endif // DATABASE_H
