#include <iostream>
#include "User.h"
#include "Reader.h"
#include "Administrator.h"
using namespace std;

int main()
{
    string a,b;
    cout << "Please enter your name and your identity~" << endl;
    getline(cin,a);
    getline(cin,b);
    User p(a,b);
    cout << "Please enter the type of the information you want to search: ";
    string type;
    cin >> type;
    cout << p.search(type) << endl;
    cout << "Your name is: " << p.getName() << ", and your identity is: " << p.getIdentity() << endl;

    return 0;
}
