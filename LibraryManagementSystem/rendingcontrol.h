#ifndef RENDINGCONTROL_H
#define RENDINGCONTROL_H
#include <database.h>
extern Database* db;
class RendControl{
public:
    void newRendRequest(const string &user_id,const string &item_id);
    void newReturnRequest(const string &item_id);
    mongocxx::cursor getBorrowList(const string &user_id);
    mongocxx::cursor getReturnList();
    void commitReturn(const string &id);
};
#endif // RENDINGCONTROL_H
