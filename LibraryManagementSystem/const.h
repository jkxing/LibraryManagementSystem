#ifndef CONST_H
#define CONST_H
#include <string>
#include <date.h>
using namespace std;
namespace CONST{
    enum loginState{
        SuccessLogin,
        WrongPassword,
        UserUnexist,
        Other
    };
    enum OrderList{
        Unknown,
        Exit,
        Register,
        Login,
        HelpPage
    };
    extern string projectName;
    extern TimeLen defaultBorrowTime;
}
#endif // CONST_H
