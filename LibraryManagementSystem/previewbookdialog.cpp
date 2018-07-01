#include "previewbookdialog.h"
#include "ui_previewbookdialog.h"

PreviewBookDialog::PreviewBookDialog(QWidget *parent,bsoncxx::document::value v) :
    QDialog(parent),
    ui(new Ui::PreviewBookDialog)
{
    ui->setupUi(this);
    ui->textEdit->setText(QString::fromStdString(bsoncxx::to_json(v.view())));
}

PreviewBookDialog::~PreviewBookDialog()
{
    delete ui;
}
