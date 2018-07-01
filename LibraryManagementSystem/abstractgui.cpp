#include "abstractgui.h"
//#include "ui_abstractgui.h"
#include <QDebug>
AbstractGui::AbstractGui(string str):User(str){

}
string AbstractGui::setData(int r,int c, bsoncxx::document::view v, QString qstr){
    QModelIndex index = model->index(r,c,QModelIndex());
    string str = qstr.toStdString();
    qDebug()<<qstr;
    //qDebug()<<QString::fromStdString(bsoncxx::to_json(v));
    if(v.find(str)!=v.end()){
        qDebug()<<"have it";
        if(str=="_id")
            str = v[str].get_oid().value.to_string();
        else
            str = v[str].get_utf8().value.to_string();
        qDebug()<<QString::fromStdString(str);
        model->setData(index,QString::fromStdString(str));
        return str;
    }
    return "";
}
