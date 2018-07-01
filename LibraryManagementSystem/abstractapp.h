#ifndef ABSTRACTAPP_H
#define ABSTRACTAPP_H
#include <stdafx.h>
#include <user.h>
using namespace std;
class AbstractApp{
public:
    AbstractApp();
    virtual int Main() = 0;//interactive function
    virtual string getInput() = 0;//get input from user
    virtual map<string,pair<string,string> > getInput(map<string,pair<string,string> > &mp) = 0;//get input from user with specify item
    virtual void ShowHelpPages() = 0;//no such thing
    virtual void showMessage(const string &str) = 0;//show message to user
    virtual void exit() = 0;//exit system
    virtual ~AbstractApp();
};
#endif // ABSTRACTAPP_H
