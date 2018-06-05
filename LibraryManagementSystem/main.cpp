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
    //cout<<"main working"<<endl;
    bsoncxx::builder::stream::document doc{};
    doc<<"bookname"<<"santi3";
    shop->addItem(doc.extract());
    end();
    return 0;
}
