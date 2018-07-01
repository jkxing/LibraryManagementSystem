#ifndef SEARCHER_H
#define SEARCHER_H
#include <database.h>
#include <vector>
using namespace std;
class Searcher{
public:
    vector<bsoncxx::document::value> search(bsoncxx::document::view info);
    vector<bsoncxx::document::value> search(bsoncxx::builder::stream::document &doc);
};
#endif // SEARCHER_H
