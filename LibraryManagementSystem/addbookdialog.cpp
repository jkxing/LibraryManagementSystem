#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include <vector>
#include <string>
#include <map>
using namespace std;
AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
    setStyleSheet("#AdminGui{border-image: url(:/image/bookbg.jpg)}");
    setWindowTitle("添加书籍");
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}
map<string,string> AddBookDialog::work(){
    map<string,string> v;
    v.clear();
    if(this->exec()==QDialog::Accepted){
        v["书名"]=ui->lineEdit->text().toStdString();
        v["作者"]=ui->lineEdit_2->text().toStdString();
        v["出版社"]=ui->lineEdit_3->text().toStdString();
        v["ISBN"]=ui->lineEdit_4->text().toStdString();
        return v;
    }
    return v;
}
