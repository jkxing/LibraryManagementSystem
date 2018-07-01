#ifndef DIALOG_H
#define DIALOG_H

#include <stdafx.h>

using namespace std;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog//Register Dialog, don't care about the misleading name QAQ
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    Dialog(int w,int h,QWidget *parent = 0);
    ~Dialog();
    map<string, pair<string, string> > work(map<string, pair<string, string> > &mp);//get Register info
private slots:

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
