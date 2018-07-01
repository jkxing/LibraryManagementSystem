#ifndef USERGUI_H
#define USERGUI_H

#include <QMainWindow>
#include <abstractgui.h>
#include <user.h>
#include <QStandardItemModel>
namespace Ui {
class userGui;
}

class userGui : public QMainWindow,public AbstractGui
{
    Q_OBJECT

public:
    explicit userGui(QWidget *parent,const string &id);
    void Main();
    ~userGui();

private slots:
    void on_Record_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_Search_clicked();

private:
    Ui::userGui *ui;
};

#endif // USERGUI_H
