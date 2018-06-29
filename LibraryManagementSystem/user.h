#ifndef USER_H
#define USER_H
#include <string>
#include <rendingcontrol.h>
#include <searcher.h>
#include <usercontrol.h>
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
    void main();
    string getid();
    string getName();
    string getIdentity();
    string search();
    ~User(){}
};

#endif // USER_H
