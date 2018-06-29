#include <searcher.h>
#include <database.h>
#include <QDebug>
#include <string>
using namespace std;
extern Database *db;
mongocxx::cursor Searcher::search(bsoncxx::document::value info){
    mongocxx::cursor ret = db->getAll("Item",info);
    string str = bsoncxx::to_json(info.view());
    qDebug()<<QString::fromStdString(str);
    return ret;
}
mongocxx::cursor Searcher::search(bsoncxx::builder::stream::document &doc){
    mongocxx::cursor ret = db->getAll("Item",doc.extract());
    string str = bsoncxx::to_json(doc.extract().view());
    qDebug()<<QString::fromStdString(str);
    return ret;
}
