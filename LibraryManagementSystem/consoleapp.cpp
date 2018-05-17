#include <consoleapp.h>
#include <iostream>
using namespace std;
string ConsoleApp::getInput(){
    cin>>str;
    return str;
}
void ConsoleApp::showMessage(const string &str){
    cout<<str<<endl;
}
void ConsoleApp::Register(){
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
void ConsoleApp::ShowHelpPages(){
    //Todo
    cout<<"Fuck you!"<<endl;
}
void ConsoleApp::exit(){
    cout<<"Bye!"<<endl;
}
string ConsoleApp::getLoginInfo(){
    showMessage("Please input username or 'exit' to exit");
    string name = getInput();
    if(name == "exit")
        return "";
    showMessage("Please input password");
    string pass = getInput();
    pair<loginState,string> res = verifyUser(name,pass);
    if(res.first==loginState::SuccessLogin)
        return res.second;
    else if(res.first==loginState::WrongPassword)
    {
        showMessage("password wrong");
        showMessage("try again");
        return getLoginInfo();
    }
    else if(res.first == loginState::UserUnexist){
        showMessage("No such user");
        showMessage("try again");
        return getLoginInfo();
    }
    else{
        showMessage("login failed");
        showMessage("try again");
        return getLoginInfo();
    }
}
