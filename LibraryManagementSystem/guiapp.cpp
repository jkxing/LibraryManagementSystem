#include "guiapp.h"
#include "ui_guiapp.h"

GuiApp::GuiApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiApp)
{
    ui->setupUi(this);
}

GuiApp::~GuiApp()
{
    delete ui;
}
int GuiApp::main()
{
    this->show();
    return 0;
}

void GuiApp::on_Login_clicked()
{
    ld = new LoginDialog(this);
    ld->show();
}
