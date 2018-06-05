#include <shop.h>
#include <database.h>
extern Database* db;
using bsoncxx::builder::basic::kvp;
void Shop::rend(const string &item_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(item_id) <<finalize;
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               "state" << "rending" << close_document << finalize);
}
void Shop::Return(const string &item_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(item_id) <<finalize;
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               "state" << "storing" << close_document << finalize);
}
void Shop::addItem(bsoncxx::document::value val){
    db->insert("Item",val);
    db->update("Item",val,document{} << "$set" << open_document <<
               "state" << "storing" << close_document << finalize);
}

void Shop::editItem(const string &_id,bsoncxx::document::value info){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(_id) <<finalize;
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
               "state" << "storing" << close_document << finalize);
}
