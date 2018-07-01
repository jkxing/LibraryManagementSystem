
#include <stdafx.h>

#include <rendingcontrol.h>
#include <abstractapp.h>
#include <usercontrol.h>
#include <consoleapp.h>
#include <searcher.h>
#include <guiapp.h>
#include <unistd.h>
#include <shop.h>
#include <date.h>

using namespace std;

AbstractApp* System;
QApplication *a;
RendControl *rc;
UserControl *uc;
Searcher *sc;
Database *db;
Shop* shop;

void parseParameters(int argc,char** argv)
{
    a = new QApplication(argc,argv);
    int c;
    while( ( c = getopt (argc, argv, "m:") ) != -1 )
    {
        switch(c)
        {
        case 'm':
            if(optarg[0]=='g')
                System = new GuiApp();
            if(optarg[0]=='c')
                System = new ConsoleApp();
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
//main -m g ---using gui
//main -m c ---using cmd
int main(int argc, char **argv)
{
    parseParameters(argc,argv);
    System->Main();
    return a->exec();
}
