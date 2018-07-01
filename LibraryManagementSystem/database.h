#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <string>
#include <thread>
#include <queue>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/cursor.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/concatenate.hpp>
using namespace std;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::concatenate;
using namespace std;
class Database{
    std::queue<thread*> threads;
    //mongocxx::instance instance;
    //mongocxx::client client;
    //mongocxx::database db;
public:
    mongocxx::pool pool;
    Database();
    ~Database();
    void test();
    void sync();
    void multiInsert(const string &str,bsoncxx::document::view item);
    void multiRemove(const string &str,bsoncxx::document::view item);
    void multiUpdate(const string &str,bsoncxx::document::view oldItem,bsoncxx::document::view newItem);
    bsoncxx::document::value get(const string &str,bsoncxx::document::view key);
    mongocxx::cursor getAll(const string &str,bsoncxx::document::view key);
    bool insert(const string &str,bsoncxx::document::view item);
    bool update(const string &str,bsoncxx::document::view oldItem,bsoncxx::document::view newItem);
    bool remove(const string &str,bsoncxx::document::view item);
    bool find(const string &str,bsoncxx::document::view key);
};
#endif // DATABASE_H
