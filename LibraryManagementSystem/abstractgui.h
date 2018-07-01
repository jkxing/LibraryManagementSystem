#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

#include <QMainWindow>
#include <user.h>
#include <database.h>
#include <QStandardItemModel>
namespace Ui {
class AbstractGui;
}

class AbstractGui : public User
{
public:
    AbstractGui(string str);
    virtual void Main() = 0;
protected:
    QStandardItemModel *model;
    int nowShow;
    string setData(int r,int c,bsoncxx::document::view v,QString qstr);
};

#endif // ABSTRACTGUI_H
