#include <QCoreApplication>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
class AbstractApp{
protected:
    //vector<User*> users;
    //vector<Book*> books;
    enum registerState{
        Success,
        UserAlreadyExists,
        UserNameInvalid,
        PasswordInvalid
    };
#ifndef DataBase
    map<string,string> userList;
#endif
public:
    virtual string getInput() = 0;
    virtual void ShowHelpPages() = 0;
    virtual void showMessage(const string &str) = 0;
    virtual void Register() = 0;
    virtual void exit() = 0;
    //vector<Books*> searchByName(const string &str);
    registerState addUser(const string &username,const string &password);
};
AbstractApp::registerState AbstractApp::addUser(const string &username,const string &password){
#ifndef DataBase
    if(userList.count(username) > 0) return UserAlreadyExists;
    else if(username.length()<5) return UserNameInvalid;
    else if(password.length()<6) return PasswordInvalid;
    userList[username]=password;
    return Success;
#endif
    //DataBase.addUser(username,password);
}
/*template<typename T>
vector<T*> AbstractApp::searchByName(const vector<string> &strs){
#ifndef DataBase
    SeacherEngine* searcher = new NameSeacher<T*>();
    searcher->work();
    return
#endif
}*/
class ConsoleApp:public AbstractApp{
    string str;
public:
    string getInput(){
        cin>>str;
        return str;
    }
    void showMessage(const string &str){
        cout<<str<<endl;
    }
    void Register(){
        this->showMessage("Please input your username:");
        string Username = getInput();
        this->showMessage("Please input your password");
        string Password = getInput();
        registerState st = addUser(Username,Password);
        if(st == Success)
            cout<<"registered Succeed"<<endl;
        else
            cout<<"registered failed"<<endl;
    }
    void ShowHelpPages(){
        //cout<<"Haha! No such thing!"<<endl;
    }
    void exit(){
        cout<<"Bye!"<<endl;
    }
};
AbstractApp* System;

void parseParameters(int argc,char* argv[])
{
    System = new ConsoleApp();
}
int parseOrder(const string &str)
{
    if(str == "exit")
        return -1;
    return 1;
}
int get_option()
{
    static string str;
    str = System->getInput();
    while(!parseOrder(str))
    {
        System->showMessage("unexpected order,please try again");
        str = System->getInput();
    }
    return parseOrder(str);
}
int main(int argc, char *argv[])
{
    parseParameters(argc,argv);
    int order;
    while((order = get_option())!=-1)
    {
        if(order == 1)
        {
            System->Register();
        }
        else
        {
            System->showMessage("Unexpected order");
        }
        //System->showMessage(to_string(order));
    }
    System->exit();
    return 0;
}
