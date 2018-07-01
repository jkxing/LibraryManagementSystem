//
#include <database.h>
#include <const.h>
#include <thread>
#include <string>
#include <QDebug>
using namespace std;
using bsoncxx::builder::basic::kvp;
Database::Database(){
    client = mongocxx::client{mongocxx::uri{}};
    db = client[CONST::projectName];
    mongocxx::collection coll = db["Item"];
    cout<<"Db init finish"<<endl;
}
Database::~Database(){
    sync();
}

void Database::sync(){
    cout<<"syncing"<<endl;
    while(!threads.empty()){
        thread* i=threads.front();
        threads.pop();
        i->join();
    }
}

void Database::multiInsert(const string &str,bsoncxx::document::value item){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    coll.insert_one(item.view());
}

void Database::multiRemove(const string &str,bsoncxx::document::value item){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    coll.delete_one(item.view());
}

void Database::multiUpdate(const string &str,bsoncxx::document::value oldItem,bsoncxx::document::value newItem){
    auto client = pool.acquire();
    auto coll = (*client)[CONST::projectName][str];
    coll.update_one(oldItem.view(),newItem.view());
    //<<"finish"<<endl;
}
bsoncxx::document::view Database::get(const string &str,bsoncxx::document::view key){
    //auto client = pool.acquire();
    //auto coll = (*client)[CONST::projectName][str];

    qDebug()<<"get "<<QString::fromStdString(bsoncxx::to_json(key));
    mongocxx::collection coll = db[str];
    bsoncxx::stdx::optional<bsoncxx::document::value> ret =  coll.find_one(key);
    if(ret)
        return *ret;
    document doc{};
    return doc.view();
}

mongocxx::cursor Database::getAll(const string &str,bsoncxx::document::view key){

    qDebug()<<"get all "<<QString::fromStdString(bsoncxx::to_json(key));
    qDebug()<<"get all from "<<QString::fromStdString(str);
    //auto client = pool.acquire();
    //auto coll = (*client)[CONST::projectName][str];
    mongocxx::collection coll = db["Item"];
    qDebug()<<"get all medium "<<QString::fromStdString(bsoncxx::to_json(key));
    mongocxx::cursor ret =  coll.find(key);
    qDebug()<<"get all over "<<QString::fromStdString(bsoncxx::to_json(key));
    return ret;
}

bool Database::insert(const string &str,bsoncxx::document::view item){
    qDebug()<<"insert "<<QString::fromStdString(bsoncxx::to_json(item));
    mongocxx::collection coll = db[str];
    coll.insert_one(item);
    //std::thread* inst = new thread(&Database::multiInsert,this,str,item);
    //threads.push(inst);
    return true;
}

bool Database::update(const string &str,bsoncxx::document::view oldItem,bsoncxx::document::view newItem){

    qDebug()<<"updateold "<<QString::fromStdString(bsoncxx::to_json(oldItem));
    qDebug()<<"update new "<<QString::fromStdString(bsoncxx::to_json(newItem));
    //std::thread *upd = new thread(&Database::multiUpdate,this,str,oldItem,newItem);
    //threads.push(upd);
    mongocxx::collection coll = db[str];
    coll.update_one(oldItem,newItem);
    return true;
}

bool Database::remove(const string &str,bsoncxx::document::view item){
    //std::thread *rem = new thread(&Database::multiRemove,this,str,item);
    //threads.push(rem);
    qDebug()<<"remove "<<QString::fromStdString(bsoncxx::to_json(item));
    mongocxx::collection coll = db[str];
    coll.delete_one(item);
    return true;
}

bool Database::find(const string &str,bsoncxx::document::view key){
   // auto client = pool.acquire();
    //auto coll = (*client)[CONST::projectName][str];
    qDebug()<<"find "<<QString::fromStdString(bsoncxx::to_json(key));
    mongocxx::collection coll = db[str];
    bsoncxx::stdx::optional<bsoncxx::document::value> result =
        coll.find_one(key);
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
void Database::test(){
    bsoncxx::builder::basic::document doc{};
    doc.append(kvp("bookname","c++bcsx"));
    doc.append(kvp("tag","c++"));

    bsoncxx::builder::stream::document sdoc{};
    sdoc << "hello" <<"world";


    cout<<"working"<<endl;
    bsoncxx::document::value info = sdoc.extract();
    mongocxx::client client{mongocxx::uri{}};
    mongocxx::database db = client[CONST::projectName];
    mongocxx::collection coll = db["test"];
    mongocxx::cursor list = coll.find(bsoncxx::builder::stream::document{}<<"hello"<<"world"<<finalize);

    for(auto item:list){
        string tmp = item["_id"].get_oid().value.to_string();
        cout<<tmp<<endl;
    }

}
