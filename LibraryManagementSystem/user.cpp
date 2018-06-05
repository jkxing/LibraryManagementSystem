#include <user.h>
#include <iostream>
using namespace std;
User::User(const string &id,const string& a,const string& b):id(id),name(a),identity(b) {}
void User::main(){
    cout<<"user_id is:"<<this->getid()<<endl;
    cout<<"user_name is"<<this->getName()<<endl;
    cout<<"user_identity is"<<this->getIdentity()<<endl;
}

string User::getid(){
    return id;
}

string User::getName(){
    return name;
}

string User::getIdentity(){
    return idetity;
}

string User::search(const string& str){
//    //书名
//    if(str=="bookname"){
//        return book(bookname).id;
//    }
//    //作者
//    if(str=="writer"){
//        return "writer";
//    }
//    //书号
//    if(str=="booknumber"){
//        return "booknumber";
//    }
//    //出版社
//    if(str=="press"){
//        return "press";
//    }
}
