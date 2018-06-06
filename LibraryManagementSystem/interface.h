#ifndef INTERFACE_H
#define INTERFACE_H
#include <QCoreApplication>
#include <QApplication>
#include <const.h>
#include <abstractapp.h>
//using namespace std;
/*
class QApplication: QCoreApplication{

};
*/
class Interface : public AbstractApp{
    string str;
public:
    Interface(int argc,char **argv);
    ~Interface();
    std::string getInput() ;
    void main();
    void ShowHelpPages() ;
    void showMessage(const string &str) ;
    void exit() ;
    std::string getLoginInfo() ;
    pair<CONST::loginState,string> verifyUser(const string &username, const string &password);
    bsoncxx::document::value getRegisterInfo();
   // virtual ~Interface();

    /*
     * ConsoleApp();
    void main();
    string getInput();
    void showMessage(const string &str);
    void ShowHelpPages();
    void exit();
    string getLoginInfo();
    bsoncxx::document::value getRegisterInfo();
    ~ConsoleApp();
     */
};
#endif // INTERFACE_H
