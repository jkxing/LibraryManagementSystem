#include "addbookdialog.h"
#include "ui_addbookdialog.h"

using namespace std;
AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
    setStyleSheet("#AddBookDialog{border-image: url(:/image/bookbg.jpg)}");
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
        v["number"]=ui->lineEdit_5->text().toStdString();
        v["标签"]=ui->lineEdit_6->text().toStdString();
        return v;
    }
    return v;
}
