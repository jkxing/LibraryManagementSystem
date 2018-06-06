#include <abstractapp.h>
#include <interface.h>
#include <helppages.h>
#include <showmessage.h>
#include <regis.h>
#include <loginpage.h>
#include <exitt.h>
#include <const.h>
#include <usercontrol.h>
#include <database.h>
#include <mainwindow.h>
#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <QDialog>
#include <QWidget>
//using namespace UI;
//using namespace std;
using bsoncxx::builder::basic::kvp;
extern AbstractApp* System;
extern UserControl* uc;
extern Database* db;
namespace mainw{
extern CONST::OrderList Order;
}
/*
    void main();
    string getInput();
    void showMessage(const string &str);
    void ShowHelpPages();
    void exit();
    string getLoginInfo();
    bsoncxx::document::value getRegisterInfo();
 * */
int arc;
char **arv;
Interface::Interface(int argc,char **argv)
{
    cout<<233<<endl;
    arc=argc;
    arv=argv;
}
Interface::~Interface()
{

}

std::string Interface::getInput(){
#ifdef _Getinput
    QString Qusername = ui->lineEdit1->text();
#endif
    QString Qusername ;
    std::string username= Qusername.toStdString();
    return username;
}

void Interface::exit()
{
 //   QMessageBox::information(NULL, "Title", "Bye!");
    exitt bye;
    bye.exec();
}
void Interface::ShowHelpPages()
{
    HelpPages hp;
    hp.show();
}
void Interface::main()
{
    /*
     * QApplication a(argc, argv);
    Login w;
    Mainwindow dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        dlg.close();
        w.show();
        return a.exec();
    }
    else return 0;
     * */
    QApplication a(arc, arv);
    Mainwindow w;
    w.exec();
    while(mainw::Order!=CONST::OrderList::Exit)
    {
        if(mainw::Order == CONST::OrderList::Register)
            uc->Register();
        else if(mainw::Order == CONST::OrderList::HelpPage)
            ShowHelpPages();
        else if(mainw::Order == CONST::OrderList::Login)
            uc->Login();
        w.exec();
    }
   // w.exec();
   /* CONST::OrderList order;
    while((order = get_option())!=CONST::OrderList::Exit)
    {
        if(order == CONST::OrderList::Register)
            uc->Register();
        else if(order == CONST::OrderList::HelpPage)
            ShowHelpPages();
        else if(order == CONST::OrderList::Login)
            uc->Login();
    }*/

    exit();
}

bool contain(const string &str,const string a)
{
    int len1=str.length(),len2=a.length();
    for(int i=0;i+len2<=len1;i++)
        if(str.substr(i,len2)==a) return true;
    return false;
}
void Interface::showMessage(const string &str)
{
    char* st=(char*)str.data();
    //QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    QMessageBox::information(NULL, "Title", st);
}
/*
void Interface::Register()
{
    Regis r;
    registerState st = addUser(r.username,r.password);
    if(st == Success)QMessageBox::about(NULL, "hint","registered Succeed");
       // cout<<"registered Succeed"<<endl;
    else QMessageBox::about(NULL, "提示","registered failed");
       // cout<<"registered failed"<<endl;
}
*/
