#include <rendingcontrol.h>
#include <stdafx.h>
#include <shop.h>
using namespace std;
using bsoncxx::builder::basic::kvp;
extern Database* db;
extern Shop* shop;
void RendControl::newRendRequest(const string &user_id,const string &item_id){

    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("user_id",user_id));
    builder.append(kvp("item_id",item_id));
    builder.append(kvp("state","borrowing"));
    Date dat;
    builder.append(kvp("borrow date",dat.toString()));
    builder.append(kvp("return date",(dat+CONST::defaultBorrowTime).toString()));

    db->insert("BorrowList",builder.view());
    shop->rend(item_id);
}
void RendControl::newReturnRequest(const string &item_id){
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("item_id",item_id));
    db->insert("ReturnList",builder.view());
    db->update("BorrowList",builder.view(),document{} << "$set" << open_document <<
               "state" << "returning" << close_document << finalize);
}

void RendControl::commitReturn(const string &item_id){
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("item_id",item_id));
    db->remove("ReturnList",builder.view());
    db->update("BorrowList",builder.view(),document{} << "$set" << open_document <<
               "state" << "finish" << close_document << finalize);
    shop->Return(item_id);
}
vector<bsoncxx::document::value> RendControl::getBorrowList(const string &user_id){

    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("user_id",user_id));
    vector<bsoncxx::document::value> v{};
#ifdef __Database
    mongocxx::cursor res = db->getAll("BorrowList",builder.view());
    for(auto i:res)
        v.push_back(document{}<<concatenate(i)<<finalize);
#endif
    return v;
}

vector<bsoncxx::document::value> RendControl::getReturnList(){
    bsoncxx::builder::basic::document builder{};
    vector<bsoncxx::document::value> v{};
#ifdef __Database
    mongocxx::cursor res = db->getAll("ReturnList",builder.view());
    for(auto i:res)
        v.push_back(document{}<<concatenate(i)<<finalize);
#endif
    return v;
}
