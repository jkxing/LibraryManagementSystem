#include <abstractapp.h>
#include "interface.h"
#include "helppages.h"
#include "showmessage.h"
#include "regis.h"
#include "loginpage.h"
#include "exitt.h"
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
std::string Interface::getInput(){
#ifdef _Getinput
    QString Qusername = ui->lineEdit1->text();
#endif
    QString Qusername ;
    std::string username= Qusername.toStdString();
    return username;
}
void Interface::ShowHelpPages()
{
    HelpPages hp;

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
    if(contain(str,"input")){
        cout<<1<<endl;
    }
    else{
        cout<<2<<endl;
    //    QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        QMessageBox::information(NULL, "Title", st);
        cout<<3<<endl;
    }
}
void Interface::Register()
{
    Regis r;
    registerState st = addUser(r.username,r.password);
    if(st == Success)QMessageBox::about(NULL, "hint","registered Succeed");
       // cout<<"registered Succeed"<<endl;
    else QMessageBox::about(NULL, "提示","registered failed");
       // cout<<"registered failed"<<endl;
}
void Interface::exit()
{
 //   QMessageBox::information(NULL, "Title", "Bye!");
    exitt bye;
}
std::string Interface::getLoginInfo()
{
    Loginpage k;

    pair<loginState,string> res = verifyUser(k.username,k.password);

    if(res.first==loginState::SuccessLogin)
    {
        //login=true;
       // ps=res.second;
        return k.password;
        //return res.second;
    }
    else if(res.first==loginState::WrongPassword)
    {
       // showMessage("password wrong");
       // showMessage("try again");
        QMessageBox::about(NULL, "提示","password wrong\n""try again");
      //  return getLoginInfo();
       // loop();
        return getLoginInfo();
     //   return ;
    }
    else if(res.first == loginState::UserUnexist){
      //  showMessage("No such user");
      //  showMessage("try again");
        QMessageBox::about(NULL, "提示","No such user\n""try again");
        return getLoginInfo();
      //  loop();
       // return ;
    }
    else{
      //  showMessage("login failed");
      //  showMessage("try again");
        QMessageBox::about(NULL, "提示","login failed\n""try again");
        return getLoginInfo();
      //  loop();
      //  return ;
    }
  //  return k.password;
    //return a;
}
