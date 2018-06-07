#ifndef ABSTRACTAPP_H
#define ABSTRACTAPP_H
#include <books.h>
#include <database.h>
#include <user.h>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;
class AbstractApp{
public:
    AbstractApp();
    virtual int main() = 0;
    virtual string getInput() = 0;
    virtual map<string,pair<string,string> > getInput(map<string,pair<string,string> > &mp) = 0;
    virtual void ShowHelpPages() = 0;
    virtual void showMessage(const string &str) = 0;
    virtual void exit() = 0;
    virtual ~AbstractApp();
};
#endif // ABSTRACTAPP_H
