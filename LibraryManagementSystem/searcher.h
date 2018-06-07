#ifndef SEARCHER_H
#define SEARCHER_H
#include <database.h>
class Searcher{
public:
    mongocxx::cursor search(bsoncxx::document::value info);
    mongocxx::cursor search(bsoncxx::builder::stream::document &doc);
};
#endif // SEARCHER_H
