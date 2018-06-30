#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent,QString str) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    setWindowTitle("Edit");
    ui->setupUi(this);
    ui->lineEdit->setText(str);
    ui->lineEdit->setReadOnly(true);
    setStyleSheet("#EditDialog{border-image: url(:/image/bookbg.jpg)}");
}

EditDialog::~EditDialog()
{
    delete ui;
}

QString EditDialog::work(){
    if(this->exec()==QDialog::Accepted){
        QString qstr = ui->lineEdit_2->text();
        if(qstr!="") return qstr;
        return ui->lineEdit->text();
    }
    return "";
}
