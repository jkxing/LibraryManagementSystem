#include "regis.h"
#include "ui_regis.h"
#include "abstractapp.h"
#include <QMessageBox>
Regis::Regis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regis)
{
    ui->setupUi(this);
}

Regis::~Regis()
{
    delete ui;
}

void Regis::on_pushButton_clicked()
{
    QString Qusername = ui->lineEdit->text();
    QString Qpassword = ui->lineEdit_2->text();
    username= Qusername.toStdString();
    password= Qpassword.toStdString();
    return ;
}
