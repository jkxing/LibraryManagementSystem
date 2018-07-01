#ifndef USER_H
#define USER_H

#include <rendingcontrol.h>
#include <confirmdialog.h>
#include <usercontrol.h>
#include <searcher.h>
#include <cstdio>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;
using namespace std;
class User{
    string id;
    string name;
    string identity;
public:
    User(const string &id);
    User(const string &id ,const string &name ,const string &identity);
    virtual void Main() = 0;
    string getid();
    string getName();
    string getIdentity();
    string search();
    virtual ~User(){}
};

#endif // USER_H
