#ifndef RENDINGCONTROL_H
#define RENDINGCONTROL_H
#include <database.h>
#include <stdafx.h>
using namespace  std;
extern Database* db;
class RendControl{//control rending/returning/commiting
public:
    //when reader will borrow a book , use this to log it
    void newRendRequest(const string &user_id,const string &item_id);

    //when reader return a book, use this to log it
    void newReturnRequest(const string &item_id);

    //when administrator confirm a book is returned,use this to handle it
    void commitReturn(const string &id);

    //reader use this to  get the books they borrowed,with book id ,borrow date,return date
    vector<bsoncxx::document::value> getBorrowList(const string &user_id);

    //admin use this to  get what books is returned but not confirmed
    vector<bsoncxx::document::value> getReturnList();
};
#endif // RENDINGCONTROL_H
