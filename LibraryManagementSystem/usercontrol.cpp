#include <usercontrol.h>
#include <database.h>
#include <abstractapp.h>
#include <string>
#include <QDebug>
#include <Reader.h>
#include <Administrator.h>
using namespace std;
extern Database* db;
extern AbstractApp* System;
using bsoncxx::builder::basic::kvp;
pair<CONST::loginState,string> UserControl::verifyUser(const string &username, const string &password){
#ifndef __Database
    if(username == "reader")
        return make_pair(CONST::loginState::SuccessReaderLogin,"reader");
    if(username == "admin")
        return make_pair(CONST::loginState::SuccessAdminLogin,"admin");
#endif
    bsoncxx::builder::basic::document builder{};
    bsoncxx::document::view passAndId{};
    builder.append(kvp("username",username));
    passAndId = db->get("User",builder.view());
    if(passAndId.empty())
        return make_pair(CONST::loginState::UserUnexist,"");
    builder.append(kvp("password",password));
    passAndId = db->get("User",builder.view());
    if(passAndId.empty())
        return make_pair(CONST::loginState::WrongPassword,"");
    else
    {
        auto tmp = passAndId.find("identity");
        while(tmp == passAndId.end())
            return verifyUser(username,password);
        if(passAndId["identity"].get_utf8().value.to_string()=="reader")
            return make_pair(CONST::loginState::SuccessReaderLogin,passAndId["_id"].get_oid().value.to_string());

        else if(passAndId["identity"].get_utf8().value.to_string()=="administrator")
            return make_pair(CONST::loginState::SuccessAdminLogin,passAndId["_id"].get_oid().value.to_string());
    }
    return make_pair(CONST::loginState::Other,"");
}

void UserControl::Register(){
    bsoncxx::document::view info = getRegisterInfo();
    if(info.empty())
       return;
    bool st = db->insert("User",info);
    if(st)
        System->showMessage("Register Success");
    else
        System->showMessage("Internal Error.Please try again");
}

void UserControl::addReader(bsoncxx::document::view usr){
    db->insert("User",usr);
}

void UserControl::removeReader(string id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(id) ;
    db->remove("User",builder.view());
}

void UserControl::Login(){
    pair<string,int> id = getLoginInfo();
    User * new_user;
    if(id.first=="")
        return;
    if(id.second==0)
        new_user = new Reader(id.first);
    else
        new_user = new Administrator(id.first);
    new_user->Main();
    delete new_user;
}

bsoncxx::document::value UserControl::getRegisterInfo(){
    bsoncxx::builder::basic::document doc;
    bsoncxx::builder::basic::document fail{};
    map< string,pair<string,string> > mp;
    mp["email"]=make_pair("","");
    mp["username"]=make_pair("","");
    mp["password"]=make_pair("","");
    mp["nickname"]=make_pair("","");
    mp = System->getInput(mp);
    if(mp.size()==0) return document{}.extract();
    string Username = mp["username"].first;
    while(Username.length()<6||db->find("User",bsoncxx::builder::basic::make_document(kvp("username", Username)))){
        if(Username.length()<6)
            mp["username"].second = "username too short";
        else
            mp["username"].second = "username already exists";
        mp = System->getInput(mp);
        if(mp.size()==0) return document{}.extract();
        Username = mp["username"].first;
    }
    string Password = mp["password"].first;
    while(Password.length()<6){
        mp["password"].second = "password too short";
        mp = System->getInput(mp);
        if(mp.size()==0) return document{}.extract();
        Password = mp["password"].first;
        cout << Password <<endl;
    }
    string Id = mp["nickname"].first;
    string Email = mp["email"].first;
    bsoncxx::builder::basic::document builder{};
    builder.append(kvp("username",Username));
    builder.append(kvp("password",Password));
    builder.append(kvp("nickname",Id));
    builder.append(kvp("email",Email));
    if(Username != "adminnn")
        builder.append(kvp("identity","reader"));
    else
        builder.append(kvp("identity","administrator"));
    return builder.extract();
}

pair<string,int> UserControl::getLoginInfo(){
    bsoncxx::builder::basic::document doc;
    map< string,pair<string,string> > mp;
    mp["Username"]=make_pair("","");
    mp["password"]=make_pair("","");
    mp = System->getInput(mp);
    string name = mp["Username"].first;
    if(name == "exit")
        return make_pair("",0);
    string pass = mp["password"].first;
    pair<CONST::loginState,string> res = verifyUser(name,pass);
    if(res.first==CONST::loginState::SuccessReaderLogin)
        return make_pair(res.second,0);
    else if(res.first==CONST::loginState::SuccessAdminLogin)
        return make_pair(res.second,1);
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
void UserControl::updateUserInfo(const string &_id,bsoncxx::document::view info){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(_id) ;
    db->update("User",builder.view(),document{} << "$set" <<
               info << finalize);
}
vector<bsoncxx::document::value> UserControl::getUserInfo(const string &user_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(user_id) ;
    vector<bsoncxx::document::value> v{};
#ifdef __Database
    mongocxx::cursor res = db->getAll("User",builder.view());
    for(auto i:res)
        v.push_back(document{}<<concatenate(i)<<finalize);
#endif
    return v;
}
