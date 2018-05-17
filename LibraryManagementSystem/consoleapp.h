#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H
#include <abstractapp.h>
class ConsoleApp:public AbstractApp{
    string str;
public:
    string getInput();
    void showMessage(const string &str);
    void ShowHelpPages();
    void Register();
    void exit();
    string getLoginInfo();
    //string verifyUser();
};
#endif // CONSOLEAPP_H
