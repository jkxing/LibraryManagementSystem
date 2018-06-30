#ifndef ADMINISTRAOE_H
#define ADMINISTRAOR_H

#include "User.h"
#include "shop.h"
#include "searcher.h"

class Administrator : public User{
public:
    Administrator(string &id) : User(id){}
    Administrator(string &id, const string &name) : User(id, name, "Administrator"){}
    void Main();
    void help();
    //添加书
    void add_book();
    //删除书
    void delete_book();
    //修改书的信息
    void modify_book();
    //审核借阅
    void check_borrow(const string& user_id);
    //审核归还
    void check_giveback();
    ~Administrator(){}
};

#endif
