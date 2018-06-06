#include "loginpage.h"
#include "ui_loginpage.h"
#include <abstractapp.h>
Loginpage::Loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginpage)
{
    ui->setupUi(this);
}

Loginpage::~Loginpage()
{
    delete ui;
}
/*
void Loginpage::loop()
{
     ui->lineEdit->clean();
     ui->lineEdit_2->clean();
     Loginpage::on_submitbutton_clicked();
}
*/
void Loginpage::on_submitbutton_clicked()
{
    QString Qusername = ui->lineEdit1->text();
    QString Qpassword = ui->lineEdit2->text();
    username= Qusername.toStdString();
    password= Qpassword.toStdString();
    return ;
}

void Loginpage::on_returnbutton_clicked()
{
    ret=1;
    close();
}
