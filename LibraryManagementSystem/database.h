#ifndef DATABASE_H
#define DATABASE_H

#include <thread>
#include <queue>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/concatenate.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/cursor.hpp>

using namespace std;

using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::concatenate;
using bsoncxx::builder::basic::kvp;

class Database{//Database
    queue<thread*> threads;
    //mongocxx::instance instance;
    //mongocxx::client client;
    //mongocxx::database db;
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
    friend class UserControl;
    friend class RendControl;
    friend class Searcher;
    friend class Shop;
public:
    mongocxx::pool pool;
    Database();
    ~Database();
};
#endif // DATABASE_H
