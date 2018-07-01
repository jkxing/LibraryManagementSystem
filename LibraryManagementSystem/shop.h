#ifndef SHOP_H
#define SHOP_H
#include <stdafx.h>

using namespace std;
class Shop{//Book shop , edit/add book
public:
    //when user rend a book,use this to update book state
    void rend(const string item_id);
    //when user return a book,use this to update book state
    void Return(const string item_id);
    //admin use this to add book
    void addItem(bsoncxx::document::view val);
    //admin use this to modify book
    void editItem(const string id,bsoncxx::document::view info);
    //user use it to get book info
    bsoncxx::document::value getallinfo(const string id);
};
#endif // SHOP_H
