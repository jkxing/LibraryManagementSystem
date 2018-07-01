#ifndef RENDINGCONTROL_H
#define RENDINGCONTROL_H
#include <database.h>
extern Database* db;
class RendControl{
public:
    void newRendRequest(const string &user_id,const string &item_id);
    void newReturnRequest(const string &item_id);
    vector<bsoncxx::document::value> getBorrowList(const string &user_id);
    vector<bsoncxx::document::value> getReturnList();
    void commitReturn(const string &id);
};
#endif // RENDINGCONTROL_H
