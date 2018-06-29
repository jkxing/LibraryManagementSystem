#ifndef USERGUI_H
#define USERGUI_H

#include <QMainWindow>
#include <user.h>
namespace Ui {
class userGui;
}

class userGui : public QMainWindow,User
{
    Q_OBJECT

public:
    explicit userGui(QWidget *parent = 0,string &id);
    void main();
    ~userGui();

private:
    Ui::userGui *ui;
};

#endif // USERGUI_H
