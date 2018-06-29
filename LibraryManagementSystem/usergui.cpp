#include "usergui.h"
#include "ui_usergui.h"
#include <user.h>

userGui::userGui(QWidget *parent,string &str) :
    QMainWindow(parent),
    ui(new Ui::userGui),
    User(str);
{
    ui->setupUi(this);
}
userGui::main(){
    this->show();
}
userGui::~userGui()
{
    delete ui;
}
