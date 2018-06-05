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
public:
    Database();
    ~Database();
    void sync();
    bsoncxx::document::value get(const string &str,bsoncxx::document::value key);
    mongocxx::cursor getAll(const string &str,bsoncxx::document::value key);
    bool insert(const string &str,bsoncxx::document::value item);
    bool update(const string &str,bsoncxx::document::value oldItem,bsoncxx::document::value newItem);
    bool remove(const string &str,bsoncxx::document::value item);
    bool find(const string &str,bsoncxx::document::value key);
};
#endif // DATABASE_H
