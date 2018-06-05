#ifndef READER_H
#define READER_H

#include "User.h"

class Reader : public User{
public:
    Reader(string a, string b):User(a,b){}
    void borrow(){}
    void giveback(){}
    void preview(){}
    ~Reader(){}
};

#endif
