#include <database.h>
mongocxx::instance Database::inst{};
mongocxx::client Database::conn{mongocxx::uri{}};

/*
 *
    filter << "_id" << bsoncxx::oid("5afda2f58726e333fc006ab2") <<finalize;
    mongocxx::cursor cursor = bookCollection.find(filter.extract());
    auto tmp = doc["_id"].get_oid().value.to_string();
*/


Database::Database(){
    borrowCollection = conn["LibraryManagementSystem"]["borrowInfo"];
    returnCollection = conn["LibraryManagementSystem"]["returnInfo"];
    userCollection = conn["LibraryManagementSystem"]["userInfo"];
    bookCollection = conn["LibraryManagementSystem"]["bookList"];
}
bool Database::existUser(const string &username)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> result =
      userCollection.find_one(document{} << "username" <<username<< finalize);
    if(result)
        return false;
    return true;
}
void Database::addUser(const string &username, const string &pass){
    bsoncxx::builder::stream::document document{};
    document << "username" <<username
             << "password" <<pass;
    userCollection.insert_one(document.view());
}
void Database::newBorrow(const string &user_id, const string &book_id){
    bsoncxx::builder::stream::document document{};
    document << "user" <<user_id
             << "book" <<book_id;
    borrowCollection.insert_one(document.view());
}
void Database::addReturn(const string &user_id, const string &book_id){
    bsoncxx::builder::stream::document document{};
    document << "user" <<user_id
             << "book" <<book_id;
    returnCollection.insert_one(document.view());
}
void Database::commitReturn(const string &book_id){
    bsoncxx::stdx::optional<bsoncxx::document::value> result =
        returnCollection.find_one(document{} << "_id" << bsoncxx::oid(book_id) << finalize);
    if(result) {
        //cout << bsoncxx::to_json(*result) << endl;
        returnCollection.delete_one(document{} << "_id" << bsoncxx::oid(book_id) << finalize);
    }
}
pair<string,string> Database::getUserPassword(const string &username){
    bsoncxx::stdx::optional<bsoncxx::document::value> result =
      userCollection.find_one(document{} << "username" <<username<< finalize);
    if(result) {
        cout << bsoncxx::to_json(*result) << endl;
        bsoncxx::document::view view = result->view();
        bsoncxx::document::element element = view["password"];
        string pass = element.get_utf8().value.to_string();
        auto _id = view["_id"].get_oid().value.to_string();
        return make_pair(pass,_id);
    }
    return make_pair("","");
}
vector<string> Database::search(const map<string, string> &keyword){
    vector<string> idList{};
    bsoncxx::builder::stream::document filter{};
    for(auto &i:keyword)
    {
        //cout<<i.first<<" "<<i.second<<endl;
        filter << i.first << i.second;
    }
    filter << finalize;
    mongocxx::cursor cursor = bookCollection.find(filter.extract());
    for(auto &doc : cursor) {
        auto tmp = doc["_id"].get_oid().value.to_string();
        idList.push_back(tmp);
    }
    return idList;
}
vector<string> Database::getBorrowedList(const string &user_id){
    vector<string> idList{};
    bsoncxx::builder::stream::document filter{};
    filter << "user" << user_id << finalize;
    mongocxx::cursor cursor = borrowCollection.find(filter.extract());
    for(auto &doc : cursor) {
        auto tmp = doc["_id"].get_oid().value.to_string();
        idList.push_back(tmp);
    }
    return idList;
}
vector<string> Database::getReturnList(){
    vector<string> idList{};
    bsoncxx::builder::stream::document filter{};
    mongocxx::cursor cursor = returnCollection.find(filter.extract());
    for(auto &doc : cursor) {
        auto tmp = doc["_id"].get_oid().value.to_string();
        idList.push_back(tmp);
    }
    return idList;
}
void Database::addBook(const map<string,string> &bookInfo){
    bsoncxx::builder::stream::document doc{};
    for(auto &i:bookInfo)
    {
        //cout<<i.first<<" "<<i.second<<endl;
        doc << i.first << i.second;
    }
    bookCollection.insert_one(doc.view());
}
