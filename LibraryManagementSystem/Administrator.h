#ifndef ADMINISTRAOE_H
#define ADMINISTRAOR_H

#include <User.h>
#include <shop.h>
#include <searcher.h>

class Administrator : public User{
public:
    Administrator(string &id) : User(id){}
    Administrator(string &id, const string &name) : User(id, name, "Administrator"){}
    //工作界面
    void Main();
    //帮助界面
    void help();
    //添加书
    void add_book();
    //修改书的信息
    void modify_book();
    //审核归还
    void check_giveback();
    ~Administrator(){}
};

#endif
