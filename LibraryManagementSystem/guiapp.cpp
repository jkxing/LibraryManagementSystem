#include "guiapp.h"
#include "ui_guiapp.h"

#include <stdafx.h>

#include <usercontrol.h>
#include <usergui.h>
#include <admingui.h>
extern UserControl* uc;
GuiApp::GuiApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiApp)
{
    ui->setupUi(this);
    setCentralWidget(ui->centralwidget);
    setStyleSheet("#GuiApp{border-image: url(:/image/bookbg.jpg)}");

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

GuiApp::~GuiApp()
{
    delete ui;
}
extern QApplication* a;
int GuiApp::Main()
{
    show();
    return 0;
}

void GuiApp::on_Login_clicked()
{
    ld = new LoginDialog(this);
    pair<string,string> pa = ld->work();
    if(pa.first!="")
    {
        pair<CONST::loginState,string> tmp = uc->verifyUser(pa.first,pa.second);
        if(tmp.first == CONST::loginState::SuccessReaderLogin)
        {
            User* user = new userGui(this,tmp.second);
            user->Main();
        }
        else if(tmp.first == CONST::loginState::SuccessAdminLogin)
        {
            User *user = new AdminGui(this,tmp.second);
            user->Main();
        }
    }
}

void GuiApp::on_Register_clicked()
{
    uc->Register();
}

map<string, pair<string, string> > GuiApp::getInput(map<string, pair<string, string> > &mp){ 
    Dialog* dia = new Dialog(800,600,this);
    mp = dia->work(mp);
    return mp;
}

void GuiApp::showMessage(const string &str){
    qDebug()<<QString::fromStdString(str);
}
