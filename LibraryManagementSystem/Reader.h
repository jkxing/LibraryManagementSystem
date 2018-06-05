#ifndef READER_H
#define READER_H

#include "User.h"

class Reader : public User{
public:
    Reader(const string& id,const string& a):User(id,a,"Reader"){}
    void borrow(const string& id){}
    void giveback(const string& id){}
    //void preview(){}
    ~Reader(){}
};
#endif
