#ifndef ADMINISTRAOE_H
#define ADMINISTRAOR_H

#include "User.h"

class Administrator : public User{
public:
    Administrator(string a, string b):User(a,b){}
    //添加书
    void add_book(string a){//a是有关于书的信息，包括书名、作者...
        /*if(//这个信息不存在)
            把这个信息转换成书储存起来;
        else
            cout << "你已经添加过这本书了~" << endl;
        */
    }
    //删除书
    void omit_book(string a){//a有关于书的信息
        /*if(//这个信息存在)
            把这个信息对应的书删除掉;
        else
            cout << "书库中还没有这本书哦~" << endl;
        */
    }
    //修改书的信息
    void modify_book(string a){//a是有关于书的信息
        /*if(//这个信息对应的书存在)
            更改对应书的相应信息;
        else
            cout << "书库中还没有这本书哦~" << endl;*/
    }
    void add_reader(){}
    void omit_reader(){}
    void modify_reader(){}
    //审核借阅
    void check_borrow(/*Reader rea,string a*/){
        

    }
    //审核归还
    void check_giveback(){}
    ~Administrator(){}
};

#endif