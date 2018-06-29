#include "Reader.h"
extern Searcher* sc;
extern RendControl* rc;
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
    cout << "(2) Enter 'Returnbook', you can Initiate a request to return a book." << endl;
    cout << "These are what we offer now. Don't be worried, we are constantly updating our system to give you a better experience. Thanks for using." << endl;
    cout << endl << "Now you can input your order to start using it." << endl;
}

void Reader::Main() {
    cout<<"user_id is:"<<this->getid()<<endl;
    cout<<"user_name is"<<this->getName()<<endl;
    cout<<"user_identity is"<<this->getIdentity()<<endl;
    cout<<"Please input order or you can see our help page by entering 'Help' at first: ";
    string str;
    cin >> str;
    if(str=="Borrowbook")
        borrow();
    else if(str=="Returnbook")
        giveback();
    else if(str=="Help")
        help();
    /*拓展功能
    else if(str=="Score")
        score();
    */
}
