#include "usergui.h"
#include "ui_usergui.h"
#include <user.h>
#include <rendingcontrol.h>
#include <QStandardItemModel>
#include <QDebug>
#include <iostream>
#include <shop.h>
#include <searchui.h>
#include <search.h>
#include <QPropertyAnimation>
using namespace std;
extern RendControl *rc;
extern Shop *shop;
extern Searcher *sc;
userGui::userGui(QWidget *parent,const string &str) :
    QMainWindow(parent),
    ui(new Ui::userGui),
    AbstractGui(str)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setStyleSheet("#userGui{border-image: url(:/image/bookbg.jpg)}");
    qDebug()<<QString::fromStdString(str);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}
void userGui::Main(){
    this->show();
}
userGui::~userGui()
{
    delete ui;
}
void userGui::on_Record_clicked()
{
    nowShow = 0;
    vector<bsoncxx::document::value> list = rc->getBorrowList(getid());
    qDebug()<<list.size();
    model = new QStandardItemModel(list.size(),5,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("bookname"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("borrow date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("return date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("state"));
    int tmp = 0;
    for(auto doc1:list)
    {
        auto doc = doc1.view();
        string str = setData(tmp,0,doc,"item_id");
        qDebug()<<"0";
        if(str!="")
        {
            bsoncxx::document::value vie = shop->getallinfo(str);
            setData(tmp,1,vie.view(),"书名");
            qDebug()<<"1";
        }
        setData(tmp,2,doc,"borrow date");
        qDebug()<<"2";
        setData(tmp,3,doc,"return date");
        qDebug()<<"3";
        setData(tmp,4,doc,"state");
        qDebug()<<"4";
        tmp++;
    }
    ui->tableView->setModel(model);
}

void userGui::on_tableView_doubleClicked(const QModelIndex &Index)
{
    if(nowShow == 0){
        ConfirmDialog confirm(this,"是否确认还书");
        if(confirm.exec()!=QDialog::Accepted)
            return;
        qDebug()<<"handling return";
        QModelIndex index = model->index(Index.row(),0);
        QString qstr = model->data(index).toString();
        qDebug()<<qstr;
        QModelIndex t = model->index(index.row(),4);
        QString qtmp = model->data(t).toString();
        string stmp = qtmp.toStdString();
        if(stmp=="borrowing")
        {
            string str = qstr.toStdString();
            model->setData(t,"returning");
            rc->newReturnRequest(str);
            qDebug()<<"new return";
        }
        else{
            qDebug()<<"already returning or finish";
        }
    }
    else{
        ConfirmDialog confirm(this,"是否确认借书");
        if(confirm.exec()!=QDialog::Accepted)
            return;
        QModelIndex index = model->index(Index.row(),4);
        qDebug()<<"handling borrow";
        QString qstr = model->data(index).toString();
        qDebug()<<qstr;
        QModelIndex t = model->index(index.row(),5);
        QString qtmp = model->data(t).toString();
        string stmp = qtmp.toStdString();
        qDebug()<<qtmp;
        if(stmp=="storing")
        {
            string str = qstr.toStdString();
            model->setData(t,"borrowed");
            rc->newRendRequest(getid(),str);
            qDebug()<<"new borrow";
        }
        else{
            qDebug()<<"already borrowed or sale";
        }
    }
}

void userGui::on_Search_clicked()
{
    nowShow = 1;
    Searchui* se = new Searchui(this);
    map<string,string> v = se->work();
    if(v.size()==0)
        return;
    bsoncxx::builder::stream::document dd;
    for(auto i:v){
        dd<<i.first<<i.second;
        qDebug()<<QString::fromStdString(i.first);
        qDebug()<<QString::fromStdString(i.second);
    }
    vector<bsoncxx::document::value> list = sc->search(dd.view());
    model = new QStandardItemModel(list.size(),6,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("书名"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("作者"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ISBN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("state"));
    int tmp = 0;
    for(auto doc:list)
    {      
        setData(tmp,0,doc.view(),"书名");
        setData(tmp,1,doc.view(),"作者");
        setData(tmp,2,doc.view(),"ISBN");
        setData(tmp,3,doc.view(),"出版社");
        setData(tmp,4,doc.view(),"_id");
        setData(tmp,5,doc.view(),"state");
        tmp++;
    }
    ui->tableView->setModel(model);
}
