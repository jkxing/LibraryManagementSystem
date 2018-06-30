#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <vector>
#include <QDebug>
#include <string>
#include <map>
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
    map<string,string> work();
private:
    Ui::AddBookDialog *ui;
};

#endif // ADDBOOKDIALOG_H
