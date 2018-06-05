#include "helppages.h"
#include "ui_helppages.h"

HelpPages::HelpPages(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpPages)
{
    ui->setupUi(this);
}

HelpPages::~HelpPages()
{
    delete ui;
}
