#include <database.h>
#include <const.h>
#include <thread>
#include <string>
using namespace std;
Database::Database():pool(mongocxx::uri{}){

}
Database::~Database(){
    //sync();
}
void Database::sync(){
    cout<<"syncing"<<endl;
    while(!threads.empty()){
        thread* i=threads.front();
        threads.pop();
        i->join();
    }
}
bsoncxx::document::value Database::get(const string &str,bsoncxx::document::value key){
    //sync();
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    bsoncxx::stdx::optional<bsoncxx::document::value> ret =  coll.find_one(key.view());
    return *ret;
}

mongocxx::cursor Database::getAll(const string &str,bsoncxx::document::value key){
    //sync();
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    mongocxx::cursor ret =  coll.find(key.view());
    return ret;
}
bool Database::insert(const string &str,bsoncxx::document::value item){

    std::thread* ins = new thread([&]{
        auto client = pool.acquire();
        auto coll = (*client)[CONST::projectName][str];
        bsoncxx::document::value val{item};
        coll.insert_one(val.view());
    });
    ins->join();
    //cout<<bsoncxx::to_json(item.view())<<endl;
    //threads.push(ins);
    return true;
}
bool Database::update(const string &str,bsoncxx::document::value oldItem,bsoncxx::document::value newItem){
    //sync();
    std::thread *upd = new thread([&]{
        auto client = pool.acquire();
        auto coll = (*client)[CONST::projectName][str];
        bsoncxx::document::value oldval{oldItem};
        bsoncxx::document::value newval{newItem};
        coll.update_one(oldval.view(),newval.view());
    });
    upd->join();
    //threads.push(upd);
    return true;
}
bool Database::remove(const string &str,bsoncxx::document::value item){
    std::thread *rem = new thread([&]{
        auto client = pool.acquire();
        auto coll = (*client)[CONST::projectName][str];
        bsoncxx::document::value val{item};
        coll.delete_one(val.view());
    });
    rem->join();
    //threads.push(rem);
    return true;
}

bool Database::find(const string &str,bsoncxx::document::value key){
    //sync();
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    bsoncxx::stdx::optional<bsoncxx::document::value> result =
      coll.find_one(key.view());
    if(result)
        return true;
    return false;
}

/*
 *
    filter << "_id" << bsoncxx::oid("5afda2f58726e333fc006ab2") <<finalize;
    mongocxx::cursor cursor = bookCollection.find(filter.extract());
    auto tmp = doc["_id"].get_oid().value.to_string();
*/
