#ifndef SHOP_H
#define SHOP_H
#include <map>
#include <string>
#include <vector>
#include <database.h>
using namespace std;
class Shop{
public:
    //virtual void sendByEmail(const string &user_id);
    void rend(const string &item_id);
    void Return(const string &item_id);
    void addItem(bsoncxx::document::value val);
    void editItem(const string &id,bsoncxx::document::value info);
    bsoncxx::document::value getallinfo(const string& id);
};
#endif // SHOP_H
