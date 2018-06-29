#include "searchui.h"
#include "ui_searchui.h"
#include <QPropertyAnimation>
#include <QDebug>
Searchui::Searchui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Searchui)
{
    ui->setupUi(this);
    setWindowTitle("Search");
    setStyleSheet("#Searchui{border-image: url(:/image/bookbg.jpg)}");

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

Searchui::~Searchui()
{
    delete ui;
}

map<string,string> Searchui::work()
{
    if(exec()==QDialog::Accepted)
    {
        string str;
        map<string,string> v;
        str = ui->name->text().toStdString();
        if(str!="") v["书名"]=str;
        str = ui->author->text().toStdString();
        if(str!="") v["作者"]=str;
        str = ui->ISBN->text().toStdString();
        if(str!="") v["ISBN"]=str;
        qDebug()<<"hahahaa";
        qDebug()<<v.size()<<endl;
        return v;
     }
    else{
        map<string,string> tmp;
        tmp.clear();
        return tmp;
    }
}

void Searchui::on_buttonBox_accepted()
{

}
