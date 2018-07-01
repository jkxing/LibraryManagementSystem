#ifndef USERCONTROL_H
#define USERCONTROL_H
#include <database.h>
#include <const.h>
#include <string>
using namespace std;
extern Database* db;
class UserControl{
public:
    bsoncxx::document::value getRegisterInfo();
    pair<string,int> getLoginInfo();
    void test();
    void Login();
    void Register();
    pair<CONST::loginState,string> verifyUser(const string &username, const string &password);
    vector<bsoncxx::document::value> getUserInfo(const string &user_id);
    void updateUserInfo(const string &id,bsoncxx::document::view info);
};
#endif // USERCONTROL_H
