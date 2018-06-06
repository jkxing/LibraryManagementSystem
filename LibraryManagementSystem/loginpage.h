#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>

namespace Ui {
class Loginpage;
}

class Loginpage : public QDialog
{
    Q_OBJECT

public:
    bool login;
    std::string password,username;
    explicit Loginpage(QWidget *parent = 0);
    ~Loginpage();

private slots:
    void on_submitbutton_clicked();

    void on_returnbutton_clicked();


private:
    void loop();
    Ui::Loginpage *ui;
};

#endif // LOGINPAGE_H
