#ifndef CONSOLEAPP_H
#define CONSOLEAPP_H
#include <abstractapp.h>
using namespace std;
class ConsoleApp:public AbstractApp{//using command line to interactive
    string str;
public:
    ConsoleApp();
    int Main();
    string getInput();
    map<string,pair<string,string> > getInput(map<string,pair<string,string> > &mp);
    void showMessage(const string &str);
    void ShowHelpPages();
    void exit();

    ~ConsoleApp();
};
#endif // CONSOLEAPP_H
