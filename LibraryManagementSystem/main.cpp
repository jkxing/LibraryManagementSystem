#include <QCoreApplication>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <abstractapp.h>
#include <consoleapp.h>
#include <shop.h>
#include <bookshop.h>
using namespace std;
enum OrderList{
    Unknown,
    Exit,
    Register,
    Login,
    HelpPage
};
AbstractApp* System;
Shop* shop;
void parseParameters(int argc,char* argv[])
{
    System = new ConsoleApp();
    shop = new bookShop();
}
OrderList parseOrder(const string &str)
{
    if(str=="a")
    {
        System->addBook();
        return OrderList::Unknown;
    }
    if(str=="s")
    {
        map<string,string> mp{};
        mp["name"]="helloworld";
        System->search(mp);
        return OrderList::Unknown;
    }
    if(str == "exit")
        return OrderList::Exit;
    if(str == "Register")
        return OrderList::Register;
    if(str == "help")
        return OrderList::HelpPage;
    if(str == "Login")
        return OrderList::Login;

    return OrderList::Unknown;
}
OrderList get_option()
{
    cout<<"Please input order: ";
    static string str;
    str = System->getInput();
    while(parseOrder(str)==OrderList::Unknown)
    {
        System->showMessage("unexpected order,please try again");
        str = System->getInput();
    }
    return parseOrder(str);
}
int main(int argc, char *argv[])
{
    parseParameters(argc,argv);
    OrderList order;
    while((order = get_option())!=OrderList::Exit)
    {
        if(order == OrderList::Register)
            System->Register();
        else if(order == OrderList::HelpPage)
            System->ShowHelpPages();
        else if(order == OrderList::Login)
            System->Login();
    }
    System->exit();
    return 0;
}
