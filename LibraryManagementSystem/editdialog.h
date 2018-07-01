#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <stdafx.h>

using namespace std;
namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog//edit book info
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent,QString str);
    QString work();
    ~EditDialog();

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
