#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H
#include <abstractapp.h>
class ConsoleApp:public AbstractApp{
    string str;
public:
    ConsoleApp();
    void main();
    string getInput();
    map<string,pair<string,string> > getInput(map<string,pair<string,string> > &mp);
    void showMessage(const string &str);
    void ShowHelpPages();
    void exit();
    string getLoginInfo();
    bsoncxx::document::value getRegisterInfo();
    ~ConsoleApp();
};
#endif // CONSOLEAPP_H
