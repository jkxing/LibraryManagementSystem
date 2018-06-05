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
    string getLoginInfo();
    void Login();
    void Register();
    pair<CONST::loginState,string> verifyUser(const string &username, const string &password);
    mongocxx::cursor getUserInfo(const string &user_id);
    void updateUserInfo(const string &id,bsoncxx::document::value info);
};
#endif // USERCONTROL_H
