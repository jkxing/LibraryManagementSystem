#include "exitt.h"
#include "ui_exitt.h"

exitt::exitt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exitt)
{
    ui->setupUi(this);
}

exitt::~exitt()
{
    delete ui;
}
