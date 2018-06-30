#include "Reader.h"
extern Searcher* sc;
extern RendControl* rc;
extern UserControl *uc;
void Reader::borrow() {
    rc->newRendRequest(getid(),search());
    cout << "id: " << getid() << " has initiated a request to borrow the book." << endl;
}

void Reader::giveback() {
    rc->newReturnRequest(search());
    cout << "id: " << getid() << " has initiated a request to return the book." << endl;
}

void Reader::help() {
    cout << "Welcome to our Library! In case that you may be confused to use the managing system, we've prepared this help page to hlep you quickly master the ability to use it." << endl;
    cout << "(1) Enter 'Borrowbook', you can initiate a request to borrow a book." << endl;
    cout << "(2) Enter 'Returnbook', you can initiate a request to return a book." << endl;
    cout << "(3) Enter 'ChangePassword', you can initiate a request to change your password." << endl;
    cout << "(4) Enter 'Exit', you can exit our system." << endl;
    cout << "These are what we offer now. Don't be worried, we are constantly updating our system to give you a better experience. Thanks for using." << endl;
    cout << endl << "Now you can input your order to start using it." << endl;
}

void Reader::changepassword() {
    cout << "Please enter your existing password." << endl;
    string password;
    cin >> password;
    auto lia = uc->getUserInfo(getid());
    for(auto doc : lia)
    {
        if(password==doc["password"].get_utf8().value.to_string())
        {
            cout << "Success! Now you can change your password. Please enter your new password." << endl;
            string newpassword;
            cin >> newpassword;
            bsoncxx::document::value tmpdoc = bsoncxx::builder::stream::document{} << "password" << newpassword << bsoncxx::builder::stream::finalize;
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
}

void Reader::Main() {
    cout<<"user_id is:"<<this->getid()<<endl;
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
