#include <QCoreApplication>
#include <iostream>
#include <string>
using namespace std;
class AbstractApp{
public:
    virtual string getInput() = 0;
    virtual void showMessage(const string &str) = 0;
    virtual void exit() = 0;
};
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
        System->showMessage(to_string(order));
    }
    System->exit();
    return 0;
    //QCoreApplication a(argc, argv);

    //return a.exec();
}
