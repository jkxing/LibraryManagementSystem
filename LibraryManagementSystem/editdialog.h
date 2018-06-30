#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <string>
using namespace std;
namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
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
