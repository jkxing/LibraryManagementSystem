#include <books.h>
#include <shop.h>
#include <abstractapp.h>
#include <vector>
extern AbstractApp* System;
Book::Book(std::string id):id(id){

}
string Book::getid(){
    return id;
}
