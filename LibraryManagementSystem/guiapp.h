#ifndef GUIAPP_H
#define GUIAPP_H

#include <stdafx.h>
#include <abstractapp.h>
#include <logindialog.h>
#include <dialog.h>

using namespace std;
namespace Ui {
class GuiApp;
}

class GuiApp : public QMainWindow,public AbstractApp//use gui to interactive with users
{
    Q_OBJECT
    LoginDialog *ld;
public:
    explicit GuiApp(QWidget *parent = 0);
    int Main();
    string getInput(){return "";};
    map<string,pair<string,string> > getInput(map<string,pair<string,string> > &mp);
    void ShowHelpPages(){};
    void showMessage(const string &str);
    void exit(){};
    ~GuiApp();
private slots:
    void on_Login_clicked();

    void on_Register_clicked();

private:
    Ui::GuiApp *ui;
};

#endif // GUIAPP_H
