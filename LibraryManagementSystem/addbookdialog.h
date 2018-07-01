#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H
#include <stdafx.h>
using namespace std;
namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = 0);
    ~AddBookDialog();
    map<string,string> work();//add a book
private:
    Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H
