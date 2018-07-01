#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <stdafx.h>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog//Login GUI
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    pair<string,string> work();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
