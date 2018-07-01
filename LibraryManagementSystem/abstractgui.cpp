#include "abstractgui.h"

AbstractGui::AbstractGui(string str):User(str){

}
string AbstractGui::setData(int r,int c, bsoncxx::document::view v, QString qstr){
    QModelIndex index = model->index(r,c,QModelIndex());
    string str = qstr.toStdString();
    if(v.find(str)!=v.end()){
        if(str=="_id")
            str = v[str].get_oid().value.to_string();
        else
            str = v[str].get_utf8().value.to_string();
        model->setData(index,QString::fromStdString(str));
        return str;
    }
    return "";
}
