#include <shop.h>
#include <database.h>
#include <QDebug>
extern Database* db;
using bsoncxx::builder::basic::kvp;
void Shop::rend(const string &item_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(item_id) ;
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               "state" << "rending" << close_document << finalize);
}
void Shop::Return(const string &item_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(item_id) ;
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               "state" << "storing" << close_document << finalize);
}
void Shop::addItem(bsoncxx::document::value val){
    db->insert("Item",val);
    db->update("Item",val,document{} << "$set" << open_document <<
               "state" << "storing" << close_document << finalize);
}

void Shop::editItem(const string &_id,bsoncxx::document::value info){
    qDebug()<<QString::fromStdString(_id);
    qDebug()<<QString::fromStdString(bsoncxx::to_json(info.view()));
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(_id) ;
    qDebug()<<"medium";
    bsoncxx::builder::stream::document doc{};
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               bsoncxx::builder::concatenate(info.view()) << close_document << finalize);
    qDebug()<<"finish";
}
bsoncxx::document::value Shop::getallinfo(const string &id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(id) ;
    qDebug()<<QString::fromStdString(id);
    return db->get("Item",builder.extract().view());
}
