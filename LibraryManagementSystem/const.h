#ifndef CONST_H
#define CONST_H
#include <string>
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
}
#endif // CONST_H
