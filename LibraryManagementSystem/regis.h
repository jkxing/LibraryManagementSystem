#ifndef REGIS_H
#define REGIS_H

#include <QDialog>

namespace Ui {
class Regis;
}

class Regis : public QDialog
{
    Q_OBJECT

public:
    explicit Regis(QWidget *parent = 0);
    ~Regis();
    std::string username,password;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Regis *ui;
};

#endif // REGIS_H
