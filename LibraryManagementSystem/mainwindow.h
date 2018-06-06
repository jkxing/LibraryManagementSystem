#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <const.h>
namespace Ui {
class Mainwindow;
}


class Mainwindow : public QDialog
{
    Q_OBJECT

public:
    int opt;
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

private slots:
    void on_registerbutton_clicked();

    void on_loginbutton_clicked();

    void on_about_clicked();

private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_H
