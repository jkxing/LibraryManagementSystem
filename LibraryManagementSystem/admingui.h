#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <user.h>
#include <map>
#include <vector>
#include <string>
using namespace std;
namespace Ui {
class AdminGui;
}

class AdminGui : public QMainWindow,public User
{
    Q_OBJECT

public:
    explicit AdminGui(QWidget *parent,const string &str);
    ~AdminGui();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void Main();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AdminGui *ui;
    QStandardItemModel *model;
    int nowShow;
};

#endif // ADMINGUI_H
