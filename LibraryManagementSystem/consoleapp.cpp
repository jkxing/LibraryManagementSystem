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
