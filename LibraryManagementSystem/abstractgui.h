#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

#include <stdafx.h>
#include <user.h>

class AbstractGui : public User
{
public:
    AbstractGui(string str);
    virtual void Main() = 0;
protected:
    int nowShow;//what is display on the screen
    QStandardItemModel *model;//tableview widget
    string setData(int r,int c,bsoncxx::document::view v,QString qstr);//set tableview data
};

#endif // ABSTRACTGUI_H
