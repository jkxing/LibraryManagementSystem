#ifndef READER_H
#define READER_H

#include "User.h"

class Reader : public User{
public:
    using User::User;
    void main();
    void borrow();
    void giveback();
    void onlinewatching();
    ~Reader();
};
#endif
