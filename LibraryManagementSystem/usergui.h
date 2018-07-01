#ifndef USERGUI_H
#define USERGUI_H

#include <abstractgui.h>

namespace Ui {
class userGui;//reader gui
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
