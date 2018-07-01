#include "Reader.h"
extern Searcher* sc;
extern RendControl* rc;
extern UserControl *uc;

Reader::~Reader(){

}

void Reader::getborrowlist() {
     auto lia = rc->getBorrowList(getid());
     int i = 1;
     for(auto doc : lia)
     {
         cout << "(" << i << ")";
         cout << bsoncxx::to_json(doc) << endl;//之后会把所有的信息全都打印出来
         i++;
     }
     cout << endl << "If the status of the book is 'borrowed', then you've already got the book!" << endl;
     cout << endl << "If the status of the book is 'checking', then you need to wait for the administrator to check your borrow request." << endl;
     cout << endl << "Now you can enter a number to continue." << endl;
     cout << endl << "If the status of the book is 'borrowed', please enter the number of the book; if not, please enter '0'." << endl << endl;
     int num;
     cin >> num;
     int k = 1;
     if(num!=0)
         for(auto doc : lia)
         {
             if(k==num)
             {
                 getNowBookId(Reader::number)=doc.view()["item_id"].get_utf8().value.to_string();
                 cout << endl << "OK!" << endl << endl;
                 Reader::number++;
                 cout << endl << "You've borrowed " << Reader::number << " book(s) by now, you can still borrow " << 10-Reader::number << " book(s)." << endl;
                 return;
             }//如果这次借阅成功了，让用户输入成功借阅的index，从而将这次成功借阅的书籍加入到记录借阅书籍的数组getNowBookId中，并修改number，提示用户还可以借阅多少书籍。
             else
                 k++;
         }
      else
         return;
}

void Reader::borrow() {
    string _id = search();
    if(_id!="")
    {
        rc->newRendRequest(getid(),_id);
        cout << endl << "You have initiated a request to borrow the book." << endl;
        cout << endl << "In order to make sure that you've successfully borrowed the book, please make sure that every time you try to borrow a book, you check the borrow list." << endl;
    }//如果正常返回书籍的id，则进行正常的借书操作
    else
        return;//否则重新进入输入指令界面
}//调用search函数，将借书请求转到rendingcontrol中

void Reader::giveback() {
    string _id = search();
    if(_id=="")
        return;
    else
    {
        int _num=0;
        for(int i=0;i<10;i++,_num++)
            if(_id==getNowBookId(i))
                break;//找到想还的书是借阅中的书的第几本
        if(_num<10)
        {
            rc->newReturnRequest(_id);
            cout << endl << "You have initiated a request to return the book." << endl;
            for(int j=_num;j<9;j++)
                getNowBookId(j)=getNowBookId(j+1);
            getNowBookId(9)="";
            Reader::number--;
            cout << endl << "Now you can borrow " << 10-Reader::number << " book(s)." << endl;
        }//如果这本书的确正在借阅才可以归还，归还之后记录书籍的数组在该书籍之后的书籍往前挪一位，number++，提示用户现在可以借阅的书籍数量。
        else
        {
            cout << endl << "Sorry, you haven't borrowed this book." << endl;
            return;
        }//如果这本书没有被该用户借阅，则提示用户没有借过这本书。
    }
}//调用search函数，将还书请求转到rendingcontrol中

void Reader::help() {
    cout << endl << "Welcome to our Library!\n\nIn case that you may be confused to use the managing system, we've prepared this help page to help you quickly master the ability to use it." << endl;
    cout << endl << "(1) Enter 'Borrowbook', you can initiate a request to borrow a book." << endl;
    cout << endl << "(2) Enter 'Returnbook', you can initiate a request to return a book." << endl;
    cout << endl << "(3) Enter 'GetBorrowList', you can get your borrow history page." << endl;
    cout << endl << "(4) Enter 'ChangePassword', you can initiate a request to change your password." << endl;
    cout << endl << "(5) Enter 'Exit', you can exit our system." << endl;
    cout << endl << "These are what we offer now. Don't be worried, we are constantly updating our system to give you a better experience. Thanks for using." << endl;
    cout << endl << "WE HAVE TO EMPHASIZE THAT YOU SHOULD ALWAYS RETURN AFTER BORROWING." << endl;
    cout << endl << "Now you can input your order to start using it." << endl;
}//给出用户的帮助界面

void Reader::changepassword() {
    cout << endl << "Please enter your existing password." << endl;
    string password;
    cin >> password;
    auto lia = uc->getUserInfo(getid());
    for(auto doc1 : lia)
    {
        auto doc = doc1.view();
        if(password==doc["password"].get_utf8().value.to_string())
        {
            cout << endl << "Success! Now you can change your password. Please enter your new password." << endl;
            string newpassword;
            cin >> newpassword;
            bsoncxx::document::view tmpdoc = bsoncxx::builder::stream::document{} << "password" << newpassword << bsoncxx::builder::stream::finalize;
            uc->updateUserInfo(getid(),tmpdoc);
            cout << endl << "Congratulations! You've finished changing your password." << endl;
        }
        else
        {
            cout << endl << "Sorry, you've entered a wrong password. Please try again." << endl;
            changepassword();
        }
    }
    return;
}//先确认用户密码，然后将请求转到usercontrol进行更换密码的处理

void Reader::Main() {
    cout<< endl << "user_id is:"<<this->getid()<<endl;
    //主要功能：借书、还书、更改密码、观看帮助、退出系统
    while(1)
    {
        cout << endl << "Please input order or you can see our help page by entering 'Help' to get mor information about our system: ";
        string str;
        cin >> str;
        if(str!="Exit"&&str!="Borrowbook"&&str!="Returnbook"&&str!="ChangePassword"&&str!="Help"&&str!="GetBorrowList")
        {
            cout << endl << "You've entered a wrong order.You may want to see the help page." << endl;
            help();
        }
        if(str=="Exit")
        {
            cout << endl << "Thanks for using our system! See you next time!" << endl;
            return;
        }
        else if(str=="Borrowbook")
            borrow();
        else if(str=="Returnbook")
            giveback();
        else if(str=="GetBorrowList")
            getborrowlist();
        else if(str=="ChangePassword")
            changepassword();
        else if(str=="Help")
            help();
    }
}
