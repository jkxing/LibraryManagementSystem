#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    setWindowTitle("Login");
    setStyleSheet("#LoginDialog{border-image: url(:/image/bookbg.jpg)}");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
pair<string,string> LoginDialog::work(){
    if(exec()==QDialog::Accepted){
        string str1 = ui->lineEdit->text().toStdString();
        string str2 = ui->lineEdit_2->text().toStdString();
        return make_pair(str1,str2);
    }
    return make_pair("","");
}
