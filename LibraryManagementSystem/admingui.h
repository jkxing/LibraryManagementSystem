#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <user.h>
#include <map>
#include <vector>
#include <string>
#include <abstractgui.h>
using namespace std;
namespace Ui {
class AdminGui;
}

class AdminGui : public QMainWindow,public AbstractGui
{
    Q_OBJECT

public:
    explicit AdminGui(QWidget *parent,const string &str);
    ~AdminGui();
    void Main();
private slots:
    void on_pushButton_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::AdminGui *ui;
};

#endif // ADMINGUI_H
