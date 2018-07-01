#include <searcher.h>
#include <database.h>
#include <QDebug>
#include <string>
#include <iostream>
using namespace std;
extern Database *db;
vector<bsoncxx::document::value> Searcher::search(bsoncxx::document::view info){
    vector<bsoncxx::document::value> v{};
#ifdef __Database
    mongocxx::cursor ret = db->getAll("Item",info);
    string str = bsoncxx::to_json(info);
    for(auto i:ret)
        v.push_back(document{}<<concatenate(i)<<finalize);
#endif
    return v;
}
vector<bsoncxx::document::value> Searcher::search(bsoncxx::builder::stream::document &doc){
    vector<bsoncxx::document::value> v{};
#ifdef __Database
    mongocxx::cursor ret = db->getAll("Item",doc.extract());
    string str = bsoncxx::to_json(doc.view());
    for(auto i:ret)
        v.push_back(document{}<<concatenate(i)<<finalize);
#endif
    return v;
}
