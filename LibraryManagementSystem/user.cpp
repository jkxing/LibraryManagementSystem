#include <user.h>
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int User::number = 0;

User::User(const string &id):id(id){

}//默认构造函数，接受常字符串为用户id

void User::Main(){

}//被Reader类重写覆盖，输出用户的相关信息

string User::getid(){
    return id;
}//返回用户id

string User::getName(){
    return name;
}//返回用户name

string User::getIdentity(){
    return identity;
}//返回用户identity

string& User::getNowBookId(int i){
    return now_book_id[i];
}

extern Searcher* sc;
string User::search(){
    //让用户输入他想查询的书的一些信息
    string bookname,writername,tag,ISBN;
    cout << endl << "Please input bookname; or input 'end': ";
    cin >> bookname;
    cout << endl << "Please input writername; or please input 'end': ";
    cin >> writername;
    cout << endl << "Please input a tag of the book; or please input 'end': ";
    cin >> tag;
    cout << endl << "Please input ISBN of the book; or please input 'end': ";
    cin >> ISBN;
    //将用户输入的信息转入到Searcher类中，进入search函数。
    auto builder = bsoncxx::builder::stream::document{};
    if(bookname!="end")
        builder << "bookname" << bookname;
    if(writername!="end")
        builder << "writername" << writername;
    if(tag!="end")
        builder << "tag" << tag;
    if(ISBN!="end")
        builder << "ISBN" << ISBN;
    bsoncxx::document::value doc_value = builder.extract();
    auto lia = sc->search(doc_value.view());//通过调用Searcher类的search函数，返回一系列符合用户输入信息的书籍（以cursor的格式）
    int i = 1;
    for(auto doc : lia)
    {
        cout << endl <<  "(" << i << ")";
        cout << bsoncxx::to_json(doc) << endl;
        i++;
    }//遍历cursor中的value，将信息全部打印出来
    if(i==1)
    {
        cout << endl << "Sorry, it seems that we don't have this book. Maybe you can look for another book." << endl;
        return "";
    }//如果返回的cursor是空的，表示库中可能不存在这本书，或者是用户输入的信息有错误，退出这次输入让用户重新输入
    //让用户继续选择具体是哪一本书，然后返回一个id；
    cout << endl << "Please enter the number of the book you are looking for." << endl;
    int num;
    cin >> num;
    int k = 1;
    for(auto doc : lia)
    {
        if(k==num)
        {
            return doc.view()["_id"].get_oid().value.to_string();
            break;
        }
        else
            k++;
    }
}
