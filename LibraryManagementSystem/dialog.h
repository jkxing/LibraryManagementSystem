#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <string>
#include <map>
using namespace std;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    Dialog(int w,int h,QWidget *parent = 0);
    ~Dialog();
    map<string, pair<string, string> > work(map<string, pair<string, string> > &mp);
private slots:

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
