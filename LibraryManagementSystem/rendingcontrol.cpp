#include <rendingcontrol.h>
#include <database.h>
#include <iostream>
#include <date.h>
#include <QDebug>
#include <const.h>
using namespace std;
using bsoncxx::builder::basic::kvp;
extern Database* db;
void RendControl::newRendRequest(const string &user_id,const string &item_id){
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("user_id",user_id));
    builder.append(kvp("item_id",item_id));
    builder.append(kvp("state","borrowing"));
    Date dat;
    builder.append(kvp("borrow date",dat.toString()));
    builder.append(kvp("return date",(dat+CONST::defaultBorrowTime).toString()));
    db->insert("BorrowList",builder.extract());
    builder.clear();
    builder.append(kvp("_id",bsoncxx::oid(item_id)));
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
                                                          "state" << "borrowed" << close_document << finalize);
}
void RendControl::newReturnRequest(const string &item_id){
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("item_id",item_id));
    db->insert("ReturnList",builder.extract());
    db->update("BorrowList",builder.extract(),document{} << "$set" << open_document <<
               "state" << "returning" << close_document << finalize);
}

void RendControl::commitReturn(const string &item_id){
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("item_id",item_id));
    db->remove("ReturnList",builder.extract());
    db->update("BorrowList",builder.extract(),document{} << "$set" << open_document <<
               "state" << "finish" << close_document << finalize);
    builder.clear();
    builder.append(kvp("_id",bsoncxx::oid(item_id)));
    db->update("Item",builder.extract(),document{} << "$set" << open_document <<
                                                          "state" << "borrowed" << close_document << finalize);
}

mongocxx::cursor RendControl::getBorrowList(const string &user_id){
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("user_id",user_id));
    mongocxx::cursor ret = db->getAll("BorrowList",builder.extract());
    return ret;
}

mongocxx::cursor RendControl::getReturnList(){
    bsoncxx::builder::basic::document builder{};
    mongocxx::cursor ret = db->getAll("ReturnList",builder.extract());
    return ret;
}
