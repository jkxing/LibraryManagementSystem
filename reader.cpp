#include "Reader.h"
extern Searcher* sc;
extern RendControl* rc;
void Reader::borrow() {
    rc->newRendRequest(getid(),search());
}

void Reader::giveback() {
    cout << "Please input the bookname: ";
    string bookname;
    cin >> bookname;
    cout << endl;
    cout << "Maybe you meant to return this(these) book(s)?" << endl;
    mongocxx::collection coll = db["item"];
    mongocxx::cursor cursor = collection.find(document{} << "bookname" << open_document << bookname << close_document << finalize);//得到所有书名为这个的书
    cout << "Here are all the possible books you may want to return." << endl;
    for(auto store : cursor)//cursor中的每一个元素都相当于一个value
        //把所有的信息全都打印出来；
    cout << "Please input the writername of the book you want to return." << endl;
    string writername;
    cin >> writername;

}

void Reader::onlinewatching() {

}

void Reader::main() {
    cout<<"user_id is:"<<this->getid()<<endl;
    cout<<"user_name is"<<this->getName()<<endl;
    cout<<"user_identity is"<<this->getIdentity()<<endl;
    cout<<"Please input order: ";
    string str;
    cin >> str;
    string bookid;
    if(str=="Borrowbook")
        borrow();
    else if(str=="Returnbook")
        giveback();
    else if(str=="Onlinewatching")
    {
        //还需要能够支持在线预览
    }
}
