#ifndef BOOKSHOP_H
#define BOOKSHOP_H
#include <books.h>
#include <shop.h>
#include <database.h>
#include <map>
#include <string>
using namespace std;
class bookShop:public Shop{
    Database *db;
public:
    bookShop();
    void send();
};
#endif // BOOKSHOP_H
