#include <QCoreApplication>
#include <QApplication>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <abstractapp.h>
#include <consoleapp.h>
#include <interface.h>
#include <rendingcontrol.h>
#include <shop.h>
#include <date.h>
#include <usercontrol.h>
#include <searcher.h>
#include <guiapp.h>
using namespace std;
using bsoncxx::builder::basic::kvp;
mongocxx::instance inst{};
AbstractApp* System;
Database *db;
RendControl *rc;
Shop* shop;
UserControl *uc;
Searcher *sc;
QApplication *a;
void parseParameters(int argc,char** argv)
{
    //ShowWindow(FindWindow("ConsoleWindowClass",argv[0]),0);
   // QApplication a(argc, argv);
 //   System = new Interface();
    a = new QApplication(argc,argv);
    System = new GuiApp();
    db = new Database();
    rc = new RendControl();
    shop = new Shop();
    uc = new UserControl();
    sc = new Searcher();
}
void end()
{
    delete System;
    delete db;
    delete rc;
    delete shop;
    delete uc;
    delete sc;
}
int main(int argc, char **argv)
{
    parseParameters(argc,argv);
    System->main();
    return a->exec();
}
