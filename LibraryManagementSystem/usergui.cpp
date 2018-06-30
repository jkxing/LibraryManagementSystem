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
    User(str)
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
    mongocxx::cursor list = rc->getBorrowList(getid());
    int cnt = 0;
    for(auto doc:list)
        cnt++;
    model = new QStandardItemModel(cnt,5,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("bookname"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("borrow date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("return date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("state"));
    int tmp = 0;
    list = rc->getBorrowList(getid());
    for(auto doc:list)
    {
        QModelIndex index = model->index(tmp,0,QModelIndex());
        string str = doc["item_id"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,1,QModelIndex());
        bsoncxx::document::value val = shop->getallinfo(str);
        bsoncxx::document::view vie = val.view();
        str = vie["书名"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,2,QModelIndex());
        str = doc["borrow date"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,3,QModelIndex());
        str = doc["return date"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,4,QModelIndex());
        str = doc["state"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
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
    mongocxx::cursor list = sc->search(dd.extract());
    int cnt = 0;
    for(auto doc:list)
        cnt++;
    qDebug()<<cnt<<endl;
    model = new QStandardItemModel(cnt,6,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("书名"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("作者"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ISBN"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("出版社"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("state"));
    int tmp = 0;
    dd.clear();
    for(auto i:v){
        dd<<i.first<<i.second;
    }
    list = sc->search(dd.extract());
    for(auto doc:list)
    {
        QModelIndex index = model->index(tmp,0,QModelIndex());
        string str = doc["书名"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,1,QModelIndex());
        str = doc["作者"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,2,QModelIndex());
        str = doc["ISBN"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,3,QModelIndex());
        str = doc["出版社"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,4,QModelIndex());
        str = doc["_id"].get_oid().value.to_string();
        model->setData(index,QString::fromStdString(str));
        index = model->index(tmp,5,QModelIndex());
        str = doc["state"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        tmp++;
    }
    ui->tableView->setModel(model);
}
