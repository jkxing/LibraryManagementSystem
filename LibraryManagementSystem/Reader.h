#ifndef READER_H
#define READER_H

#include <user.h>

class Reader : public User{
public:
    using User::User;
    void Main();
    void borrow();
    void giveback();
    void help();
    void changepassword();
    void getborrowlist();
    //void
    ~Reader();
};
#endif
