#include "Reader.h"
extern Searcher* sc;
extern RendControl* rc;
extern UserControl *uc;

Reader::~Reader(){

}

void Reader::borrow() {
    rc->newRendRequest(getid(),search());
    cout << "id: " << getid() << " has initiated a request to borrow the book." << endl;
    //下面的部分是试验中的现有借阅
    cout << "Now you can enter 'ShowBorrowList' to see if you've successfully borrowed the book (and at the same time you will get to know your borrow history)." << endl;
    string str;
    cin >> str;
    while(1)
    {
        if(str=='ShowBorrowList')
        {
            auto lia = rc->getBorrowList(getid());
            int i = 1;
            for(auto doc : lia)
            {
                cout << "(" << i << ")";
                cout << bsoncxx::to_json(doc) << endl;//之后会把所有的信息全都打印出来
                i++;
            }
            cout << "If the status of the book is 'borrowed', then you've already got the book! Please continue to enter the number of the book." << endl;
            cout << "If the status of the book is 'checking', then you need to wait for the administrator to check your borrow request." << endl;
            int num;
            cin >> num;
            int k = 1;
            for(auto doc : lia)
            {
                if(k==num)
                {
                    this->getNowBookId()=doc.view()["id"].get_utf8().value.to_string();
                    cout << "OK!" << endl;
                    break;
                }
                else
                    k++;
            }
        }
        else
            cout << "Wrong order or unknown function. Please enter again." << endl;
    }
}//调用search函数，将借书请求转到rendingcontrol中

void Reader::giveback() {
    rc->newReturnRequest(search());
    cout << "id: " << getid() << " has initiated a request to return the book." << endl;
}//调用search函数，将还书请求转到rendingcontrol中

void Reader::help() {
    cout << "Welcome to our Library! In case that you may be confused to use the managing system, we've prepared this help page to hlep you quickly master the ability to use it." << endl;
    cout << "(1) Enter 'Borrowbook', you can initiate a request to borrow a book." << endl;
    cout << "(2) Enter 'Returnbook', you can initiate a request to return a book." << endl;
    cout << "(3) Enter 'ChangePassword', you can initiate a request to change your password." << endl;
    cout << "(4) Enter 'Exit', you can exit our system." << endl;
    cout << "These are what we offer now. Don't be worried, we are constantly updating our system to give you a better experience. Thanks for using." << endl;
    cout << endl << "Now you can input your order to start using it." << endl;
}//给出用户的帮助界面

void Reader::changepassword() {
    cout << "Please enter your existing password." << endl;
    string password;
    cin >> password;
    auto lia = uc->getUserInfo(getid());
    for(auto doc1 : lia)
    {
        auto doc = doc1.view();
        if(password==doc["password"].get_utf8().value.to_string())
        {
            cout << "Success! Now you can change your password. Please enter your new password." << endl;
            string newpassword;
            cin >> newpassword;
            bsoncxx::document::view tmpdoc = bsoncxx::builder::stream::document{} << "password" << newpassword << bsoncxx::builder::stream::finalize;
            uc->updateUserInfo(getid(),tmpdoc);
            cout << "Congratulations! You've finished changing your password." << endl;
        }
        else
        {
            cout << "Sorry, you've entered a wrong password. Please try again." << endl;
            changepassword();
        }
    }
    return;
}//先确认用户密码，然后将请求转到usercontrol进行更换密码的处理

void Reader::Main() {
    cout<<"user_id is:"<<this->getid()<<endl;
    //主要功能：借书、还书、更改密码、观看帮助、退出系统
    while(1)
    {
        cout<<"Please input order or you can see our help page by entering 'Help' at first: ";
        string str;
        cin >> str;
        if(str!="Exit"&&str!="Borrowbook"&&str!="Returnbook"&&str!="ChangePassword"&&str!="Help")
        {
            cout << "You've entered a wrong order.You may want to see the help page.";
            help();
        }
        if(str=="Exit")
            return;
        else if(str=="Borrowbook")
            borrow();
        else if(str=="Returnbook")
            giveback();
        else if(str=="ChangePassword")
            changepassword();
        else if(str=="Help")
            help();
    }
}
