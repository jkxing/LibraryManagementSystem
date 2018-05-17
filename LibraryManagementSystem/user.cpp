#include <user.h>
#include <iostream>
using namespace std;
User::User(const string &id):id(id){

}
void User::main(){
    cout<<"user_id is:"<<this->id<<endl;
}
