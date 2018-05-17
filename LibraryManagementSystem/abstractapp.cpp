#include <abstractapp.h>
AbstractApp::AbstractApp(){
    db=new Database();
}
AbstractApp::registerState AbstractApp::addUser(const string &username,const string &password){
#ifndef __Database
    if(userList.count(username) > 0) return UserAlreadyExists;
    else if(username.length()<5) return UserNameInvalid;
    else if(password.length()<6) return PasswordInvalid;
    userList[username]=password;
    return Success;
#endif
    showMessage("using database");
    db->addUser(username,password);
    return Success;
}
void AbstractApp::borrowBook(User *user,Book* books){
    db->newBorrow("user->getid()","books->getid()");
    //books->borrowOne();
}
void AbstractApp::returnBook(User *user,Book* books)
{
    db->addReturn("user->getid()","books->getid()");
}
void AbstractApp::commitReturn(Book* book){
    db->commitReturn("book->getid()");
    //books->returnOne(book->getid());
}
void AbstractApp::Login(){
    string id = getLoginInfo();
    if(id=="")
        return;
    User* new_user = new User(id);
    users.push_back(new_user);
    new_user->main();
    delete new_user;
}
pair<AbstractApp::loginState,string> AbstractApp::verifyUser(const string &username, const string &password){
    pair<string,string> passAndId = db->getUserPassword(username);
    if(passAndId.second=="")
        return make_pair(loginState::UserUnexist,"");
    else if(passAndId.first!=password)
        return make_pair(loginState::WrongPassword,"");
    return make_pair(loginState::SuccessLogin,passAndId.second);
}
