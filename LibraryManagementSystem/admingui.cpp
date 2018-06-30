#include "admingui.h"
#include "ui_admingui.h"
#include <user.h>
#include <rendingcontrol.h>
#include <QStandardItemModel>
#include <QDebug>
#include <iostream>
#include <shop.h>
#include <searchui.h>
#include <search.h>
#include <QPropertyAnimation>
#include <editdialog.h>
#include <addbookdialog.h>
using namespace std;
extern RendControl *rc;
extern Shop *shop;
extern Searcher *sc;
AdminGui::AdminGui(QWidget *parent,const string &str) :
    QMainWindow(parent),
    ui(new Ui::AdminGui),
    User(str)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setStyleSheet("#AdminGui{border-image: url(:/image/bookbg.jpg)}");
    qDebug()<<QString::fromStdString(str);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

AdminGui::~AdminGui()
{
    delete ui;
}

void AdminGui::on_pushButton_clicked()
{
    nowShow = 0;
    mongocxx::cursor list = rc->getReturnList();
    int cnt = 0;
    for(auto doc:list)
        cnt++;
    model = new QStandardItemModel(cnt,3,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("bookname"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("book state"));
    int tmp = 0;
    list = rc->getReturnList();
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
        str = vie["state"].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        tmp++;
    }
    ui->tableView->setModel(model);
}

void AdminGui::on_tableView_clicked(const QModelIndex &index)
{
    if(nowShow == 0){
        ConfirmDialog confirm(this,"是否确认书籍已归还");
        if(confirm.exec()!=QDialog::Accepted)
            return;
        qDebug()<<"handling return";
        QModelIndex bookId = model->index(index.row(),0);
        QString qstr = model->data(bookId).toString();
        qDebug()<<qstr;
        QModelIndex bookStateIndex = model->index(index.row(),2);
        QString qtmp = model->data(bookStateIndex).toString();
        string stmp = qtmp.toStdString();
        qDebug()<<qtmp;
        if(stmp!="storing")
        {
            string str = qstr.toStdString();
            model->setData(bookStateIndex,"storing");
            rc->commitReturn(str);
            qDebug()<<"new commit";
        }
        else{
            qDebug()<<"already back";
        }
    }
    else if(nowShow == 1){
        qDebug()<<"handling edit";
        QString qstr = model->data(index).toString();
        qDebug()<<qstr;
        EditDialog tmp(this,qstr);
        qstr = tmp.work();
        qDebug()<<qstr;
        string str = qstr.toStdString();
        if(str!="")
        {
            model->setData(index,qstr);
            QModelIndex bookIDIndex = model->index(index.row(),4);
            string id = model->data(bookIDIndex).toString().toStdString();
            string header = model->headerData(index.column(),Qt::Horizontal).toString().toStdString();
            bsoncxx::builder::stream::document doc{};
            doc<<header<<str;
            shop->editItem(id,doc.extract());
        }
    }
}

void AdminGui::Main(){
    this->show();
    return;
}

void AdminGui::on_pushButton_2_clicked()
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

void AdminGui::on_pushButton_3_clicked()
{
    AddBookDialog a(this);
    map<string,string> res = a.work();
    if(res.size()==0) return;
    bsoncxx::builder::stream::document doc{};
    for(auto i:res){
        doc << i.first << i.second;
    }
    shop->addItem(doc.extract());
}
