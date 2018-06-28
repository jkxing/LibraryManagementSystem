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
#include <unistd.h>
#include <cstdlib>

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
    a = new QApplication(argc,argv);
    while( ( c = getopt (argc, argv, "m:") ) != -1 )
    {
        switch(c)
        {
        case 'm':
            if(optarg=="gui") System = new GuiApp();
            if(optarg=="console") System = new ConsoleApp();
            break;
        }
    }
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
    end();
    return a->exec();
}
