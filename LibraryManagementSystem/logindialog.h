#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <string>
using namespace std;
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
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
