#include <books.h>
#include <shop.h>
#include <abstractapp.h>
#include <vector>
extern AbstractApp* System;
Book::Book(std::string id):id(id){
    vector<string> v;
    v.clear();
    v.push_back("name");
    map<string,string> tmp = System->getBookInfo(this,v);
    name = tmp["name"];
}
string Book::getid(){
    return id;
}
