#include <abstractapp.h>
AbstractApp::registerState AbstractApp::addUser(const string &username,const string &password){
#ifndef __Database
    if(userList.count(username) > 0) return UserAlreadyExists;
    else if(username.length()<5) return UserNameInvalid;
    else if(password.length()<6) return PasswordInvalid;
    userList[username]=password;
    return Success;
#endif
    //DataBase.addUser(username,password);
}
void AbstractApp::HandleBorrow(){

}
void AbstractApp::Login(){
    User* new_user = new User();
    //users.push_back(new_user);
    new_user->main();
    delete new_user;
}
