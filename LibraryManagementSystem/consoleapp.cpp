#include <consoleapp.h>
#include <abstractapp.h>
#include <iostream>
#include <usercontrol.h>
using namespace std;
using bsoncxx::builder::basic::kvp;
extern AbstractApp* System;
extern UserControl* uc;
extern Database* db;

ConsoleApp::ConsoleApp(){

}
ConsoleApp::~ConsoleApp(){

}
CONST::OrderList parseOrder(const string &str)
{
    if(str == "exit")
        return CONST::OrderList::Exit;
    if(str == "Register")
        return CONST::OrderList::Register;
    if(str == "help")
        return CONST::OrderList::HelpPage;
    if(str == "Login")
        return CONST::OrderList::Login;
    return CONST::OrderList::Unknown;
}

CONST::OrderList get_option()
{
    cout<<"Please input order: ";
    static string str;
    str = System->getInput();
    while(parseOrder(str)==CONST::OrderList::Unknown)
    {
        System->showMessage("unexpected order,please try again");
        str = System->getInput();
    }
    return parseOrder(str);
}

int ConsoleApp::Main()
{
    CONST::OrderList order;
    while((order = get_option())!=CONST::OrderList::Exit)
    {
        if(order == CONST::OrderList::Register)
            uc->Register();
        else if(order == CONST::OrderList::HelpPage)
            ShowHelpPages();
        else if(order == CONST::OrderList::Login)
            uc->Login();
    }
    exit();
}

string ConsoleApp::getInput(){
    cin>>str;
    return str;
}
map<string,pair<string,string> > ConsoleApp::getInput(map<string,pair<string,string> > &mp){
    for(auto &item:mp){
        string notice = "Please input your " + item.first + " ";
        if(item.second.second != "")
            notice = notice + "("+item.second.second+")";
        notice = notice +": ";
        showMessage(notice);
        if(item.second.first!="")
            showMessage(item.second.first + " (if you input '-' and this will be used) ");
        string tmp = getInput();
        if(tmp!="-")
            item.second.first = tmp;
    }
    return mp;
}

void ConsoleApp::showMessage(const string &str){
   // cout<<233<<endl;
    cout<<str<<endl;
}

void ConsoleApp::ShowHelpPages(){
    //Todo
    cout<<"Fuck you!"<<endl;
}
void ConsoleApp::exit(){
    cout<<"Bye!"<<endl;
}

