#include <user.h>
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
User::User(const string &id):id(id){

}

User::User(const string& id, const string& name, const string& identity):id(id),name(name),identity(identity){

}
void User::Main(){
//    cout<<"user_id is:"<<this->getid()<<endl;
//    cout<<"user_name is"<<this->getName()<<endl;
//    cout<<"user_identity is"<<this->getIdentity()<<endl;
}

string User::getid(){
    return id;
}

string User::getName(){
    return name;
}

string User::getIdentity(){
    return identity;
}
extern Searcher* sc;
string User::search(){
    string bookname,writername="",tags[5];
    cout << endl << "Please input bookname: ";
    cin >> bookname;
    cout << endl << "Please input writername: ";
    cin >> writername;
    cout << endl << "If possible, please input some tags of the book; or please inout 'end': ";
    for(int i=0;i<5;i++)
    {
        cin >> tags[i];
        if(tags[i]=="end")
        {
            tags[i]="";
            break;
        }
    }
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder << "bookname" << bookname << "writername" << writername << "tags" << bsoncxx::builder::stream::open_array << tags[0] << tags[1] << tags[2] << tags[3] << tags[4] << bsoncxx::builder::stream::close_array << finalize;
    auto lia = sc->search(doc_value.view());
    int i = 1;
    for(auto doc : lia)
    {
        cout << "(" << i << ")";
        cout << bsoncxx::to_json(doc) << endl;//之后会把所有的信息全都打印出来
        i++;
    }
    //让用户继续选择具体是哪一本书，然后我返回一个id；
    cout << "Please enter the number of the book you are looking for." << endl;
    int num;
    cin >> num;
    int k = 1;
    for(auto doc : lia)
    {
        if(k==num)
        {
            cout << "Here is the id of the book:";
            cout << doc.view()["id"].get_utf8().value.to_string() << endl;
            return doc.view()["id"].get_utf8().value.to_string();
            break;
        }
        else
            k++;
    }
    return "";
}
