#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <stdafx.h>

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog //confirm borrowing/returning/commiting
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent, QString str);
    ~ConfirmDialog();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
