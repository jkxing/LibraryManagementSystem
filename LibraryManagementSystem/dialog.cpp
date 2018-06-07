#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QPropertyAnimation>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Register");
}
Dialog::Dialog(int w,int h,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(w,h);
    setWindowTitle("Register");
    setStyleSheet("#Dialog{border-image: url(:/image/bookbg.jpg)}");

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}
Dialog::~Dialog()
{
    delete ui;
}
map<string, pair<string, string> > Dialog::work(map<string, pair<string, string> > &mp){
    if(exec()==QDialog::Accepted)
    {
        QString str1 = ui->lineEdit->text();
        QString str2 = ui->lineEdit_2->text();
        QString str3 = ui->lineEdit_3->text();
        QString str4 = ui->lineEdit_4->text();
        qDebug()<<str1<<" "<<str2<<" "<<str3<<" "<<str4<<endl;
        mp["email"].first = str1.toStdString();
        mp["username"].first = str2.toStdString();
        mp["nickname"].first = str3.toStdString();
        mp["password"].first = str4.toStdString();
        return mp;
    }
}

