#include <searcher.h>
#include <database.h>
#include <QDebug>
#include <string>
#include <iostream>
using namespace std;
extern Database *db;
vector<bsoncxx::document::view> Searcher::search(bsoncxx::document::view info){
    mongocxx::cursor ret = db->getAll("Item",info);
    cout<<"insearch"<<endl;
    string str = bsoncxx::to_json(info);
    cout<<str<<endl;
    vector<bsoncxx::document::view> v{};
    for(auto i:ret)
        v.push_back(i);
    return v;
}
vector<bsoncxx::document::view> Searcher::search(bsoncxx::builder::stream::document &doc){
    mongocxx::cursor ret = db->getAll("Item",doc.extract());
    string str = bsoncxx::to_json(doc.extract().view());
    vector<bsoncxx::document::view> v{};
    for(auto i:ret)
        v.push_back(i);
    return v;
}
