#include "Administrator.h"
#include <sstream>
extern Shop* shop;
extern Searcher* sc;

void Administrator::add_book(){
    string str;
    int label;
    bsoncxx::builder::basic::document basic_builder{};
    cout << "Please input the name of the book..." << endl;
    cin >> str;
    basic_builder.append(kvp("bookname", str));
    cout << "Please input the name of the author..." << endl;
    cin >> str;
    basic_builder.append(kvp("authorname", str));

    cout << "If there's any translator... (Y/N)" << endl;
    cin >> str;
    if (str == "Y" || str == "y")
    {
        cout << "Please input the name(s) of the translator(s)..." << endl;
        cin >> str;
        basic_builder.append(kvp("translator", str));
    }

    cout << "Please input the number of label(s)..." << endl;
    cin >> label;
    bsoncxx::builder::basic::document another_builder{};
    for (int i=0; i<label; i++)
    {
        cout << "Please input a label..." << endl;
        cin >> str;
        stringstream stream;
        string count;
        stream << i;
        stream >> count;
        another_builder.append(kvp(count, str));
    }
    basic_builder.append(kvp("label", another_builder));

    cout << "Please input the press..." << endl;
    cin >> str;
    basic_builder.append(kvp("press", str));
    cout << "Please input the time of publication..." << endl;
    cin >> str;
    basic_builder.append(kvp("time", str));
    cout << "please input the introduction..." << endl;
    cin >> str;
    basic_builder.append(kvp("introduction", str));
    cout << "Please input the ISBN number..." << endl;
    cin >> str;
    basic_builder.append(kvp("ISBN", str));
    bsoncxx::document::value document = basic_builder.extract();
    if(sc->search(document).begin() == sc->search(document).end())
        shop->addItem(document);
    else cout << "This book has already been added." << endl;
}

void Administrator::delete_book(){
    string str;
    int choice;
    string info[6] = {"bookname", "authorname", "translator", "press",
                    "ISBN", "that's all"};
    bool choosed[6] = {0, 0, 0, 0, 0, 0};
    bsoncxx::builder::basic::document basic_builder{};

    cout << "Let's find the book first." << endl;
    cout << "What infomation do you have about the book?" << endl;
    for (int i = 0; i < 6; i++)
        cout << (i+1) << ". " << info[i] << endl;
    while (cin >> choice)
    {
        cout << endl;
        if (!choosed[choice])
        {
            cout << "You have input this already. Choose again." << endl;
            continue;
        }
        if (choice == 6) break;
        if (choice >= 7 || choice <= 0)
        {
            cout << "Invalid number. Choose again." << endl;
            continue;
        }
        if (choice == 1)
        {
            cout << "Please input the name of the book..." << endl;
            cin >> str;
            basic_builder.append(kvp("bookname", str));
        }
        if (choice == 2)
        {
            cout << "Please input the name of the author..." << endl;
            cin >> str;
            basic_builder.append(kvp("authorname", str));
        }
        if (choice == 3)
        {
            cin >> str;
            cout << "Please input the name(s) of the translator(s)..." << endl;
            cin >> str;
            basic_builder.append(kvp("translator", str));
        }
        if (choice == 4)
        {
            cout << "Please input the press..." << endl;
            cin >> str;
            basic_builder.append(kvp("press", str));
        }
        if (choice == 5)
        {
            cout << "Please input the ISBN number..." << endl;
            cin >> str;
            basic_builder.append(kvp("ISBN", str));
        }
        choosed[choice] = true;
        cout << "What infomation do you have about the book?" << endl;
        for (int i = 0; i < 6; i++)
            cout << (i+1) << ". " << info[i] << endl;
    }

    bsoncxx::document::value document = basic_builder.extract();
    mongocxx::cursor found = sc->search(document);
    if(found.begin() == found.end())
        cout << "This book does not exist." << endl;
    else
    {
        auto iter1 = found.begin();
        auto iter2 = found.end();
        int num = 0;
        while (iter1 != iter2)
        {
            iter1++;
            num++;
        }
        string* book = new string[num];
        int i = 0;
        for (auto doc : found)
        {
            cout << endl;
            stringstream str;
            str << bsoncxx::to_json(doc);
            str >> book[i];
            i++;
            cout << i << "." << endl;
            cout << bsoncxx::to_json(doc) << endl;
        }
        cout << endl;
        cout << "Choose one... (0 for quit)" << endl;
        cin >> i;
        while (!(i >= 0 && i <= num))
        {
            cout << "Invalid number." << endl;
            cout << "Please choose again..." << endl;
            cin >> i;
        }
        if (i == 0)
        {
            cout << "Search failed..." << endl;
            return;
        }
        else
        {
            i--;
            //shop->delete(document{} << "bookname" << book[i] << finalize);
        }
    }
}

void Administrator::modify_book(){
    /*if(//这个信息对应的书存在)
        更改对应书的相应信息;
    else
        cout << "书库中还没有这本书哦~" << endl;*/
}
//审核借阅
void Administrator::check_borrow(/*Reader rea,string a*/){

};
//审核归还
void Administrator::check_giveback(){

};
