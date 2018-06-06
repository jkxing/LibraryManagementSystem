#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <const.h>

namespace mainw{
    CONST::OrderList Order;
}
Mainwindow::Mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
 //   opt=0;
    mainw::Order=CONST::OrderList::Exit;
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::on_registerbutton_clicked()
{
    mainw::Order=CONST::OrderList::Register;
    close();
}

void Mainwindow::on_loginbutton_clicked()
{
    mainw::Order=CONST::OrderList::Login;
    close();
}

void Mainwindow::on_about_clicked()
{
    mainw::Order=CONST::OrderList::HelpPage;
    close();
}
