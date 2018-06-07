#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    setStyleSheet("#LoginDialog{border-image: url(:/image/bookbg.jpg)}");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
