#include <usercontrol.h>
#include <database.h>
#include <abstractapp.h>
#include <string>
#include <QDebug>
#include <Reader.h>
using namespace std;
extern Database* db;
extern AbstractApp* System;
using bsoncxx::builder::basic::kvp;
pair<CONST::loginState,string> UserControl::verifyUser(const string &username, const string &password){
    bsoncxx::builder::basic::document builder{};
    bsoncxx::document::view passAndId{};
    builder.append(kvp("username",username));
    passAndId = db->get("User",builder.extract()).view();
    if(passAndId.empty())
        return make_pair(CONST::loginState::UserUnexist,"");
    builder.clear();
    builder.append(kvp("username",username));
    builder.append(kvp("password",password));
    passAndId = db->get("User",builder.extract());
    if(passAndId.empty())
    {
        return make_pair(CONST::loginState::WrongPassword,"");
    }
    else if(passAndId["identity"].get_utf8().value.to_string()=="reader")
        return make_pair(CONST::loginState::SuccessReaderLogin,passAndId["_id"].get_oid().value.to_string());
    else if(passAndId["identity"].get_utf8().value.to_string()=="administrator")
        return make_pair(CONST::loginState::SuccessAdminLogin,passAndId["_id"].get_oid().value.to_string());
}

void UserControl::Register(){
    bsoncxx::document::value info = getRegisterInfo();
    bsoncxx::document::view tmp = info.view();
    if(tmp.empty())
       return;
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
    User* new_user = new Reader(id);
    new_user->Main();
    delete new_user;
}

bsoncxx::document::value UserControl::getRegisterInfo(){

    qDebug()<<"hahaha"<<endl;
    bsoncxx::builder::basic::document doc;
    bsoncxx::builder::basic::document fail{};
    map< string,pair<string,string> > mp;
    mp["email"]=make_pair("","");
    mp["username"]=make_pair("","");
    mp["password"]=make_pair("","");
    mp["nickname"]=make_pair("","");
    mp = System->getInput(mp);
    qDebug()<<"lalala"<<endl;
    if(mp.size()==0) return fail.extract();
    string Username = mp["username"].first;
    //cout<<Username<<endl;
    while(Username.length()<6||db->find("User",bsoncxx::builder::basic::make_document(kvp("username", Username)))){
        if(Username.length()<6)
            mp["username"].second = "username too short";
        else
            mp["username"].second = "username already exists";
        mp = System->getInput(mp);
        if(mp.size()==0) return fail.extract();
        Username = mp["username"].first;
    }
    string Password = mp["password"].first;
    while(Password.length()<6){
        mp["password"].second = "password too short";
        mp = System->getInput(mp);
        if(mp.size()==0) return fail.extract();
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
    builder.append(kvp("identity","reader"));
    return builder.extract();
}

string UserControl::getLoginInfo(){
    bsoncxx::builder::basic::document doc;
    map< string,pair<string,string> > mp;
    mp["username"]=make_pair("","");
    mp["password"]=make_pair("","");
    mp = System->getInput(mp);
    string name = mp["username"].first;
    if(name == "exit")
        return "";
    string pass = mp["password"].first;
    pair<CONST::loginState,string> res = verifyUser(name,pass);
    if(res.first==CONST::loginState::SuccessReaderLogin||res.first==CONST::loginState::SuccessAdminLogin)
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
void UserControl::updateUserInfo(const string &_id,bsoncxx::document::value info){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(_id) ;
    bsoncxx::document::value val = builder.extract();
    cout<<bsoncxx::to_json(val)<<endl;
    db->update("User",val,document{} << "$set" <<
               info << finalize);
}
mongocxx::cursor UserControl::getUserInfo(const string &user_id){
    bsoncxx::builder::stream::document builder{};
    builder << "_id" << bsoncxx::oid(user_id) ;
    bsoncxx::document::value val = builder.extract();
    return db->getAll("User",val);
}
