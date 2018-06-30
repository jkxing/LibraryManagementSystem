#include "confirmdialog.h"
#include "ui_confirmdialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent,QString str) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
    setWindowTitle(str);
    setStyleSheet("#ConfirmDialog{border-image: url(:/image/bookbg.jpg)}");
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}
