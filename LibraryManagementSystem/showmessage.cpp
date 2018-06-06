#include "showmessage.h"
#include "ui_showmessage.h"

ShowMessage::ShowMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowMessage)
{
    ui->setupUi(this);
}

ShowMessage::~ShowMessage()
{
    delete ui;
}
