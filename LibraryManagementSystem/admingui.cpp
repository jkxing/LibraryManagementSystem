#include "admingui.h"
#include "ui_admingui.h"
#include <user.h>
#include <rendingcontrol.h>
#include <usercontrol.h>

#include <addbookdialog.h>
#include <editdialog.h>
#include <searchui.h>
#include <search.h>
#include <dialog.h>
#include <shop.h>

using namespace std;

extern RendControl *rc;
extern UserControl *uc;
extern Shop *shop;
extern Searcher *sc;

AdminGui::AdminGui(QWidget *parent,const string &str) :
    QMainWindow(parent),
    ui(new Ui::AdminGui),
    AbstractGui(str)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setStyleSheet("#AdminGui{border-image: url(:/image/bookbg.jpg)}");
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    setWindowTitle("Welcome, administrator");
    ui->tabWidget->setAttribute(Qt::WA_TranslucentBackground);
    ui->tabWidget->setStyleSheet("background-color: transparent");

    ui->pushButton->setText("编辑图书");
    ui->pushButton_2->setText("添加图书");
}

AdminGui::~AdminGui()
{
    delete ui;
}

void AdminGui::Main(){
    this->show();
    return;
}

void AdminGui::on_pushButton_clicked()
{
    nowShow = 0;
    if(page == 2)
    {
        vector<bsoncxx::document::value> list = rc->getReturnList();
        model = new QStandardItemModel(list.size(),3,this);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("bookname"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("book state"));
        int tmp = 0;
        for(auto doc1:list)
        {
            auto doc = doc1.view();
            string str = setData(tmp,0,doc,"item_id");
            bsoncxx::document::value val = shop->getallinfo(str);
            bsoncxx::document::view vie = val.view();
            setData(tmp,1,vie,"书名");
            setData(tmp,2,vie,"state");
            tmp++;
        }
        ui->tableView_3->setModel(model);
    }
    if(page == 1){
        vector<bsoncxx::document::value> list = sc->searchByAdmin("User",bsoncxx::document::view());
        model = new QStandardItemModel(list.size(),4,this);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("username"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("password"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("identity"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("_id"));
        int tmp = 0;
        for(auto doc1:list)
        {
            auto doc = doc1.view();
            string str = setData(tmp,0,doc,"username");
            setData(tmp,1,doc,"password");
            setData(tmp,2,doc,"identity");
            setData(tmp,3,doc,"_id");
            tmp++;
        }
        ui->tableView_2->setModel(model);
    }
    if(page == 0){
        Searchui* se = new Searchui(this);
        map<string,string> v = se->work();
        if(v.size()==0)
            return;
        bsoncxx::builder::stream::document dd{};
        if(!v.count("all"))
        {
            for(auto i:v)
                dd<<i.first<<i.second;
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
        for(auto doc1:list)
        {
            auto doc = doc1.view();
            setData(tmp,0,doc,"书名");
            setData(tmp,1,doc,"作者");
            setData(tmp,2,doc,"ISBN");
            setData(tmp,3,doc,"出版社");
            setData(tmp,4,doc,"_id");
            setData(tmp,5,doc,"state");
            tmp++;
        }
        ui->tableView->setModel(model);
    }
}

void AdminGui::on_pushButton_2_clicked()
{
    nowShow = 1;
    if(page == 2)
    {
        vector<bsoncxx::document::value> list = rc->getBorrowList();
        model = new QStandardItemModel(list.size(),4,this);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("item_id"));
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("user_id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("bookname"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("book state"));
        int tmp = 0;
        for(auto doc1:list)
        {
            auto doc = doc1.view();
            string str = setData(tmp,0,doc,"item_id");
            bsoncxx::document::value val = shop->getallinfo(str);
            bsoncxx::document::view vie = val.view();
            setData(tmp,1,doc,"user_id");
            setData(tmp,2,vie,"书名");
            setData(tmp,3,vie,"state");
            tmp++;
        }
        ui->tableView_3->setModel(model);
    }
    if(page == 1)
    {
        Dialog dia(this);
        map<string,pair<string,string> > mp;
        mp.clear();
        mp = dia.work(mp);
        bsoncxx::builder::stream::document doc{};
        for(auto i:mp)
            doc<<i.first<<i.second.first;
        uc->addReader(doc.view());
    }
    if(page == 0){
        AddBookDialog a(this);
        map<string,string> res = a.work();
        if(res.size()==0) return;
        bsoncxx::builder::stream::document doc{};
        for(auto i:res){
            doc << i.first << i.second;
        }
        shop->addItem(doc.view());
    }
}

void AdminGui::on_tabWidget_currentChanged(int index)
{
    page = index;
    if(index == 0){
        ui->pushButton->setText("编辑图书");
        ui->pushButton_2->setText("添加图书");
    }
    if(index == 1){
        ui->pushButton->setText("编辑用户");
        ui->pushButton_2->setText("添加用户");
    }
    if(index == 2){
        ui->pushButton->setText("确认还书");
        ui->pushButton_2->setText("确认借书");
    }
}


void AdminGui::on_tableView_clicked(const QModelIndex &index)
{
    if(nowShow == 0)
    {
        if(index.column()==4) {
            string str = model->data(index).toString().toStdString();
            ConfirmDialog del(this,"确认删除此书吗");
            if(del.exec()==QDialog::Accepted)
                shop->removeItem(str);
            return;
        }
        qDebug()<<"handling edit book";
        QString qstr = model->data(index).toString();
        EditDialog tmp(this,qstr);
        qstr = tmp.work();
        string str = qstr.toStdString();
        if(str!="")
        {
            model->setData(index,qstr);
            QModelIndex bookIDIndex = model->index(index.row(),4);
            string id = model->data(bookIDIndex).toString().toStdString();
            string header = model->headerData(index.column(),Qt::Horizontal).toString().toStdString();
            bsoncxx::builder::stream::document doc{};
            doc<<header<<str;
            shop->editItem(id,doc.view());
        }
    }
}

void AdminGui::on_tableView_2_clicked(const QModelIndex &index)
{
    if(nowShow == 0)
    {
        if(index.column()==3){
            string str = model->data(index).toString().toStdString();
            ConfirmDialog del(this,"确认删除此用户吗");
            if(del.exec()==QDialog::Accepted)
                uc->removeReader(str);
            return;
        }
        qDebug()<<"handling edit user";
        QString qstr = model->data(index).toString();
        EditDialog tmp(this,qstr);
        qstr = tmp.work();
        string str = qstr.toStdString();
        if(str!="")
        {
            model->setData(index,qstr);
            QModelIndex bookIDIndex = model->index(index.row(),3);
            string id = model->data(bookIDIndex).toString().toStdString();
            string header = model->headerData(index.column(),Qt::Horizontal).toString().toStdString();
            bsoncxx::builder::stream::document doc{};
            doc<<header<<str;
            uc->updateUserInfo(id,doc.view());
        }
    }
}


void AdminGui::on_tableView_3_clicked(const QModelIndex &index)
{
    if(nowShow == 0){
        ConfirmDialog confirm(this,"是否确认书籍已归还");
        if(confirm.exec()!=QDialog::Accepted)
            return;
        QModelIndex bookId = model->index(index.row(),0);
        QString qstr = model->data(bookId).toString();
        qDebug()<<qstr;
        QModelIndex bookStateIndex = model->index(index.row(),2);
        QString qtmp = model->data(bookStateIndex).toString();
        string stmp = qtmp.toStdString();
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
    if(nowShow == 1){
        ConfirmDialog confirm(this,"是否确认借阅此书");
        if(confirm.exec()!=QDialog::Accepted)
            return;
        QModelIndex bookId = model->index(index.row(),0);
        QString qstr = model->data(bookId).toString();
        qDebug()<<qstr;
        QModelIndex bookStateIndex = model->index(index.row(),2);
        QString qtmp = model->data(bookStateIndex).toString();
        string stmp = qtmp.toStdString();
        if(stmp!="storing")
        {
            string str = qstr.toStdString();
            model->setData(bookStateIndex,"borrowed");
            rc->commitBorrow(str);
            qDebug()<<"new commitborrow";
        }
        else{
            qDebug()<<"already borrowed";
        }
    }
}
