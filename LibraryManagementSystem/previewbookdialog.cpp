#include "previewbookdialog.h"
#include "ui_previewbookdialog.h"

PreviewBookDialog::PreviewBookDialog(QWidget *parent,bsoncxx::document::value v) :
    QDialog(parent),
    ui(new Ui::PreviewBookDialog)
{
    ui->setupUi(this);
    setStyleSheet("#PreviewBookDialog{border-image: url(:/image/bookbg.jpg)}");
    bsoncxx::document::view vie = v.view();
    if(vie.find("书名") != vie.end())
        ui->bookname->setText(QString::fromStdString(vie["书名"].get_utf8().value.to_string()));
    if(vie.find("作者") != vie.end())
        ui->author->setText(QString::fromStdString(vie["作者"].get_utf8().value.to_string()));
    if(vie.find("ISBN") != vie.end())
        ui->isbn->setText(QString::fromStdString(vie["ISBN"].get_utf8().value.to_string()));
    if(vie.find("出版社") != vie.end())
        ui->publisher->setText(QString::fromStdString(vie["出版社"].get_utf8().value.to_string()));
    if(vie.find("编辑推荐") != vie.end())
        ui->preview->setText(QString::fromStdString(vie["编辑推荐"].get_utf8().value.to_string()));
    if(vie.find("number") != vie.end())
        ui->number->setText(QString::fromStdString(vie["number"].get_utf8().value.to_string()));
    if(vie.find("标签") != vie.end())
    {
        string str = "";
        if(vie["标签"].type()==bsoncxx::type::k_utf8)
            str = vie["标签"].get_utf8().value.to_string();
        if(vie["标签"].type()==bsoncxx::type::k_array)
            for(auto i:vie["标签"].get_array().value)
                str = str+i.get_utf8().value.to_string()+" ";
        ui->tag->setText(QString::fromStdString(str));
    }
}

PreviewBookDialog::~PreviewBookDialog()
{
    delete ui;
}
