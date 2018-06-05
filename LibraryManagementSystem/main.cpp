//#include <QCoreApplication>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <abstractapp.h>
#include <consoleapp.h>
#include <rendingcontrol.h>
#include <shop.h>
#include <usercontrol.h>
#include <searcher.h>
using namespace std;
mongocxx::instance inst{};
AbstractApp* System;
Database *db;
RendControl *rc;
Shop* shop;
UserControl *uc;
Searcher *sc;
void parseParameters(int argc,char** argv)
{
    System = new ConsoleApp();
    db = new Database();
    rc = new RendControl();
    shop = new Shop();
    uc = new UserControl();
    sc = new Searcher();
}
int main(int argc, char **argv)
{
    parseParameters(argc,argv);
    //cout<<"main working"<<endl;
    uc->Register();
    return 0;
}
