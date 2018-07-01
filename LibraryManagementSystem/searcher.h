#ifndef SEARCHER_H
#define SEARCHER_H
#include <database.h>
#include <vector>
using namespace std;
class Searcher{
public:
    vector<bsoncxx::document::view> search(bsoncxx::document::view info);
    vector<bsoncxx::document::view> search(bsoncxx::builder::stream::document &doc);
};
#endif // SEARCHER_H
