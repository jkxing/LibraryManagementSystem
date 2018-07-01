//
#include <database.h>
#include <const.h>
#include <stdafx.h>

using namespace std;

Database::Database():pool(mongocxx::uri{}){
    //client = mongocxx::client{mongocxx::uri{}};
    //db = client[CONST::projectName];
}

Database::~Database(){
    sync();
}

void Database::sync(){
    qDebug()<<"syncing"<<endl;
    while(!threads.empty()){
        thread* i=threads.front();
        threads.pop();
        i->join();
    }
}

void Database::multiInsert(const string &str,bsoncxx::document::view item){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    coll.insert_one(item);
}

void Database::multiRemove(const string &str,bsoncxx::document::view item){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    coll.delete_one(item);
}

void Database::multiUpdate(const string &str,bsoncxx::document::view oldItem,bsoncxx::document::view newItem){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    coll.update_one(oldItem,newItem);
}
bsoncxx::document::value Database::get(const string &str,bsoncxx::document::view key){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];

    //mongocxx::collection coll = db[str];
    bsoncxx::stdx::optional<bsoncxx::document::value> ret =  coll.find_one(key);
    if(ret)
        return *ret;
    document doc{};
    return doc.extract();
}

mongocxx::cursor Database::getAll(const string &str,bsoncxx::document::view key){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    //mongocxx::collection coll = db[str];
    mongocxx::cursor ret =  coll.find(key);
    return ret;
}

bool Database::insert(const string &str,bsoncxx::document::view item){

    std::thread* inst = new thread(&Database::multiInsert,this,str,item);
    //threads.push(inst);
    inst->join();
    return true;
}

bool Database::update(const string &str,bsoncxx::document::view oldItem,bsoncxx::document::view newItem){

    std::thread *upd = new thread(&Database::multiUpdate,this,str,oldItem,newItem);
    upd->join();
    //mongocxx::collection coll = db[str];
    //coll.update_one(oldItem,newItem);
    return true;
}

bool Database::remove(const string &str,bsoncxx::document::view item){
    std::thread *rem = new thread(&Database::multiRemove,this,str,item);
    rem->join();
    //threads.push(rem);
    //mongocxx::collection coll = db[str];
    //coll.delete_one(item);
    return true;
}

bool Database::find(const string &str,bsoncxx::document::view key){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    //mongocxx::collection coll = db[str];
    bsoncxx::stdx::optional<bsoncxx::document::value> result =
        coll.find_one(key);
    if(result)
        return true;
    return false;
}

