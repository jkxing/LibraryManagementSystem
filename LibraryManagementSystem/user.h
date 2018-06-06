#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User{
    string id;
    string name="zhangsan";
    string identity="reader";
public:
    User(string a, string b){
        name = a;
        identity = b;
    }
    string getName(){
        return name;
    }
    string getIdentity(){
        return identity;
    }
    string search(string str){}
    virtual ~User(){}
    User(const string &id);
    string getid();
    void main();
};

#endif // USER_H
