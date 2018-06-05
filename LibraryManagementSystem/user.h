#ifndef USER_H
#define USER_H
#include <string>
#include "rendingcontrol.h"

using namespace std;
class User{
    string id;
    string name;
    string identity;
public:
    User(const string &id,const string& a,const string& b){}
    void main();
    string getid();
    string getName(){}
    string getIdentity(){}
    string search(const string& str){}
    virtual ~User(){}
};

#endif // USER_H
