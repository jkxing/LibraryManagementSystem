#ifndef SEARCHER_H
#define SEARCHER_H

#include <stdafx.h>

using namespace std;
class Searcher{//search engine
    friend class Administrator;
    friend class AdminGui;
    vector<bsoncxx::document::value> searchByAdmin(const string &str,bsoncxx::document::view info);
public:
    //basic search
    vector<bsoncxx::document::value> search(bsoncxx::document::view info);
    vector<bsoncxx::document::value> search(bsoncxx::builder::stream::document &doc);
};
#endif // SEARCHER_H
