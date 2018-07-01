#include <shop.h>
#include <database.h>
#include <QDebug>
#include <iostream>
using namespace std;
extern Database* db;
using bsoncxx::builder::basic::kvp;
void Shop::rend(const string item_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(item_id) ;
    bsoncxx::document::value val = db->get("Item",builder.view());
    string snum = val.view()["number"].get_utf8().value.to_string();
    int num = stoi(snum);
    db->update("Item",builder.view(),document{} << "$set" << open_document <<
               "state" << "borrowed" << "number" << to_string(num-1) << close_document << finalize);
}
void Shop::Return(const string item_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(item_id) ;
    bsoncxx::document::value val = db->get("Item",builder.view());
    string snum = val.view()["number"].get_utf8().value.to_string();
    int num = stoi(snum);
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               "state" << "storing" << "number" << to_string(num+1)<< close_document << finalize);
}
void Shop::addItem(bsoncxx::document::view val){
    db->insert("Item",val);
    db->update("Item",val,document{} << "$set" << open_document <<
               "state" << "storing" << close_document << finalize);
}

void Shop::editItem(const string _id,bsoncxx::document::view info){
    qDebug()<<QString::fromStdString(_id);
    //cout<<bsoncxx::to_json(info);
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(_id) ;
    qDebug()<<"medium";
    bsoncxx::builder::stream::document doc{};
    db->update("Item",builder.view(),document{} << "$set" << open_document <<
               bsoncxx::builder::concatenate(info) << close_document << finalize);
    qDebug()<<"finish";
}


void Shop::removeItem(const string &_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(_id) ;
    db->remove("Item",builder.view());
}

bsoncxx::document::value Shop::getallinfo(const string id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(id);
    bsoncxx::document::value ret = db->get("Item",builder.view());
    if(ret.view().find("_id")!=ret.view().end())
        qDebug()<<QString::fromStdString(bsoncxx::to_json(ret.view()));
    return ret;
}
