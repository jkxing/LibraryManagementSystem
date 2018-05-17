#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User{
    string name="zhangsan";
    string identity="reader";
public:
	User(){}
    User(string a, string b){
        name = a;
        identity = b;
    }
    string getName(){
        return name;
    }
    string getIdentity(){
        return identity;
    }

    //各种检索，这里可以写"please enter information which you want to check"，然后让用户输入bookname...
    string search(string str){
        //书名
        if(str=="bookname"){
            return "bookname";
        }
        //作者
        if(str=="writer"){
            return "writer";
        }
        //书号
        if(str=="booknumber"){
            return "booknumber"; 
        }
        //出版社
        if(str=="press"){
            return "press";
        }
        //借阅状态
        if(str=="borrowing_state"){
            return "borrowing_state";
        }
        //馆藏数
        if(str=="collctionnumber"){
            return "collctionnumber";
        }
        //电子版
        if(str=="elctronic_edition"){
            return "elctronic_edition";
        }
    }
    virtual ~User(){}
};

#endif
