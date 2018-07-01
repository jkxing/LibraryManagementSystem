#ifndef CONST_H
#define CONST_H

#include <date.h>

using namespace std;
namespace CONST{//some const thing
    enum loginState{
        SuccessReaderLogin,
        SuccessAdminLogin,
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
