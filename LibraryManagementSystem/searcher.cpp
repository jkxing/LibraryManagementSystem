#include <searcher.h>
#include <database.h>
extern Database *db;
mongocxx::cursor Searcher::search(bsoncxx::document::value info){
    mongocxx::cursor ret = db->getAll("Item",info);
    return ret;
}
mongocxx::cursor Searcher::search(bsoncxx::builder::stream::document &doc){
    mongocxx::cursor ret = db->getAll("Item",doc.extract());
    return ret;
}
