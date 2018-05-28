#include <database.h>
mongocxx::instance Database::inst{};
mongocxx::client Database::conn{mongocxx::uri{}};
Database::Database(){
    borrowCollection = conn["LibraryManagementSystem"]["borrowInfo"];
    returnCollection = conn["LibraryManagementSystem"]["returnInfo"];
    userCollection = conn["LibraryManagementSystem"]["userInfo"];
    bookCollection = conn["LibraryManagementSystem"]["bookList"];
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
      returnCollection.find_one(document{} << "book" << book_id << finalize);
    if(result) {
        cout << bsoncxx::to_json(*result) << endl;
        returnCollection.delete_one(document{} << "book" << book_id << finalize);
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
        string id = username;
        return make_pair(pass,id);
    }
    return make_pair("","");
}
vector<string> Database::search(const map<string, string> &keyword){
    vector<string> idList{};
    bsoncxx::builder::stream::document filter{};
    for(auto &i:keyword)
    {
        cout<<i.first<<" "<<i.second<<endl;
        filter << i.first << i.second;
    }
    filter << finalize;
    mongocxx::cursor cursor = bookCollection.find(filter.extract());
    for(auto &doc : cursor) {
        cout<<bsoncxx::to_json(doc)<<endl;
        auto tmp = doc["id"];
        cout<< tmp.get_utf8().value.to_string() <<endl;
        idList.push_back(tmp.get_utf8().value.to_string());
    }
    return idList;
}
void Database::addBook(){
    int num = rand();
    bsoncxx::builder::stream::document document{};
    document << "id" << "book"+to_string(num)
             << "name" << "helloworld";
    bookCollection.insert_one(document.view());
}
