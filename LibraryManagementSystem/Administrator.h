#ifndef ADMINISTRAOE_H
#define ADMINISTRAOR_H

#include "User.h"
#include "shop.h"
#include "searcher.h"

class Administrator : public User{
public:
    Administrator(string a, string b):User(a,b){}
    //添加书
    void add_book(){
        string str;
        int label;
        bsoncxx::builder::basic::document basic_builder{};
        cout << "请输入书名..." << endl;
        cin >> str;
        basic_builder.append(kvp("书名", str));
        cout << "请输入作者..." << endl;
        cin >> str;
        basic_builder.append(kvp("作者", str));

        cout << "是否有翻译人员？Y/N" << endl;
        cin >> str;
        if (str == "Y" || str == "y")
        {
            cout << "请输入译者..." << endl;
            cin >> str;
            basic_builder.append(kvp("书名", str));
        }

        cout << "请输入标签个数..." << endl;
        cin >> label;
        bsoncxx::builder::basic::document another_builder{};
        for (int i=0; i<label; i++)
        {
            cout << "请输入一个标签..." << endl;
            cin >> str;
            stringstream stream;
            string count;
            stream << i;
            stream >> count;
            another_builder.append(kvp(count, str));
        }
        basic_builder.append(kvp("标签", another_builder));

        cout << "请输入出版社..." << endl;
        cin >> str;
        basic_builder.append(kvp("出版社", str));
        cout << "请输入出版时间..." << endl;
        cin >> str;
        basic_builder.append(kvp("出版时间", str));
        cout << "请输入推荐语..." << endl;
        cin >> str;
        basic_builder.append(kvp("推荐语", str));
        cout << "请输入ISBN编号..." << endl;
        cin >> str;
        basic_builder.append(kvp("ISBN", str));
        bsoncxx::document::value document = basic_builder.extract();
        if(searcher::search(document) != nullptr)
            shop::addItem(document);
        else
            cout << "你已经添加过这本书了~" << endl;
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
