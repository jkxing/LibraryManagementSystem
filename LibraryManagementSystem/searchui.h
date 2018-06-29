#ifndef SEARCHUI_H
#define SEARCHUI_H

#include <QDialog>
#include <vector>
#include <string>
using namespace std;
namespace Ui {
class Searchui;
}

class Searchui : public QDialog
{
    Q_OBJECT

public:
    explicit Searchui(QWidget *parent = 0);
    ~Searchui();
    map<string,string> work();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Searchui *ui;
};

#endif // SEARCHUI_H
