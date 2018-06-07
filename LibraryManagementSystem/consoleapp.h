#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H
#include <abstractapp.h>
class ConsoleApp:public AbstractApp{
    string str;
public:
    ConsoleApp();
    int main();
    string getInput();
    map<string,pair<string,string> > getInput(map<string,pair<string,string> > &mp);
    void showMessage(const string &str);
    void ShowHelpPages();
    void exit();

    ~ConsoleApp();
};
#endif // CONSOLEAPP_H
