#include "guiapp.h"
#include "ui_guiapp.h"
#include <usercontrol.h>
#include <QDebug>
#include <QPixmap>
#include <QSplashScreen>
#include <QPropertyAnimation>
#include <usergui.h>
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
int GuiApp::main()
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
        if(tmp.first == CONST::loginState::SuccessLogin)
        {
            User* user = new userGui(this,tmp.second);
            user->Main();
            qDebug()<<"logout";
        }
    }
}

void GuiApp::on_Help_clicked()
{

}

void GuiApp::on_Register_clicked()
{
    uc->Register();
}

map<string, pair<string, string> > GuiApp::getInput(map<string, pair<string, string> > &mp){
    qDebug()<<"Enter"<<endl;
    Dialog* dia = new Dialog(800,600,this);
    mp = dia->work(mp);
    qDebug()<<"finish"<<endl;
    return mp;
}
