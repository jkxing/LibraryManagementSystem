#ifndef INTERFACE_H
#define INTERFACE_H
#include <QCoreApplication>
#include "abstractapp.h"
//using namespace std;
/*
class QApplication: QCoreApplication{

};
*/
class Interface : public AbstractApp{
    string str;
public:
    std::string getInput() ;
    void ShowHelpPages() ;
    void showMessage(const string &str) ;
    void Register() ;
    void exit() ;
    std::string getLoginInfo() ;
   // virtual ~Interface();
};
#endif // INTERFACE_H
