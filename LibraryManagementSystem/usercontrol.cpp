#include <usercontrol.h>
#include <database.h>
#include <abstractapp.h>
#include <string>
using namespace std;
extern Database* db;
extern AbstractApp* System;
using bsoncxx::builder::basic::kvp;
pair<CONST::loginState,string> UserControl::verifyUser(const string &username, const string &password){
    bsoncxx::builder::basic::document builder{};
    bsoncxx::document::view passAndId{};
    builder.append(kvp("username",username));
    passAndId = db->get("User",builder.extract());
    if(passAndId["_id"].get_oid().value.to_string()=="")
        return make_pair(CONST::loginState::UserUnexist,"");
    builder.append(kvp("password",password));
    passAndId = db->get("User",builder.extract());
    if(passAndId["_id"].get_oid().value.to_string()=="")
        return make_pair(CONST::loginState::WrongPassword,"");
    return make_pair(CONST::loginState::SuccessLogin,passAndId["_id"].get_oid().value.to_string());
}

void UserControl::Register(){
    bsoncxx::document::value info = getRegisterInfo();
    bool st = db->insert("User",info);
    if(st)
        System->showMessage("Register Success");
    else
        System->showMessage("Internal Error.Please try again");
}

void UserControl::Login(){
    string id = getLoginInfo();
    if(id=="")
        return;
    User* new_user = new User(id);
    new_user->main();
    delete new_user;
}

bsoncxx::document::value UserControl::getRegisterInfo(){
    System->showMessage("Please input your username:");
    string Username = System->getInput();
    while(Username.length()<6||db->find("User",bsoncxx::builder::basic::make_document(kvp("username", Username)))){
        if(Username.length()<6)
            System->showMessage("username too short");
        else
            System->showMessage("username already exists");
        System->showMessage("please input your username again");
        Username = System->getInput();
    }
    System->showMessage("username valid!");
    System->showMessage("Please input your password");
    string Password = System->getInput();
    while(Password.length()<6){
        System->showMessage("password too short");
        System->showMessage("please input your password again");
        Password = System->getInput();
    }
    System->showMessage("Please input your ID");
    string Id = System->getInput();
    System->showMessage("Please input your email");
    string Email = System->getInput();
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("username",Username));
    builder.append(kvp("password",Password));
    builder.append(kvp("nickname",Id));
    builder.append(kvp("email",Email));
    return builder.extract();
}

string UserControl::getLoginInfo(){
    System->showMessage("Please input username or 'exit' to exit");
    string name = System->getInput();
    if(name == "exit")
        return "";
    System->showMessage("Please input password");
    string pass = System->getInput();
    pair<CONST::loginState,string> res = verifyUser(name,pass);
    if(res.first==CONST::loginState::SuccessLogin)
        return res.second;
    else if(res.first==CONST::loginState::WrongPassword)
    {
        System->showMessage("password wrong");
        System->showMessage("try again");
        return getLoginInfo();
    }
    else if(res.first == CONST::loginState::UserUnexist){
        System->showMessage("No such user");
        System->showMessage("try again");
        return getLoginInfo();
    }
    else{
        System->showMessage("login failed");
        System->showMessage("try again");
        return getLoginInfo();
    }
}
