#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User{
    string id;
public:
    User(const string &id);
    string getid();
    void main();
};
#endif // USER_H
