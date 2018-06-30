#include "Administrator.h"
#include <sstream>
extern Shop* shop;
extern Searcher* sc;
extern RendControl* rc;
extern Database* db;

bsoncxx::document::value find_book(){
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
        if (choice == 6) break;
        if (choosed[choice])
        {
            cout << "You have input this already. Choose again." << endl;
            continue;
        }
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
    return basic_builder.extract();
}

bsoncxx::document::value check_book(mongocxx::cursor& list, mongocxx::cursor& list2){
    auto builder = bsoncxx::builder::stream::document{};
    if(list.begin() == list.end())
    {
        cout << "No request is waiting for confirmation yet." << endl;
        bsoncxx::document::value key = builder
                << "wtf" << "wtf"
                << bsoncxx::builder::stream::finalize;
        return db->get("Item", key);
    }
    else
    {
        auto iter1 = list2.begin();
        auto iter2 = list2.end();
        int num = 0;
        while (iter1 != iter2)
        {
            iter1++;
            num++;
        }
        string* bookname = new string[num+1];
        string* authorname = new string[num+1];
        string* ISBN = new string[num+1];
        int i = 0;
        for (auto doc : list)
        {
            i++;
            bookname[i] = doc["书名"].get_utf8().value.to_string();
            authorname[i] = doc["作者"].get_utf8().value.to_string();
            ISBN[i] = doc["ISBN"].get_utf8().value.to_string();
            cout<<i<<"."<<ISBN[i]<<endl;
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
            cout << "Search failed." << endl;
            bsoncxx::document::value x = document{}.extract();
            return x;
        }
        builder.clear();
        bsoncxx::document::value key = builder
                << "ISBN" << ISBN[i]
                << bsoncxx::builder::stream::finalize;
        return db->get("Item", key);
    }
}

bsoncxx::document::value get_book(){
    string str;
    int choice;
    string info[9] = {"bookname", "authorname", "translator", "press",
                    "publication time", "label", "introduction", "ISBN", "that's all"};
    bool choosed[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    bsoncxx::builder::basic::document basic_builder{};

    cout << "What infomation do you have about the book?" << endl;
    for (int i = 0; i < 9; i++)
        cout << (i+1) << ". " << info[i] << endl;
    while (cin >> choice)
    {
        if (choice == 9) break;
        if (choosed[choice])
        {
            cout << "You have input this already. Choose again." << endl;
            continue;
        }
        if (choice >= 10 || choice <= 0)
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
            cout << "Please input publication time..." << endl;
            cin >> str;
            basic_builder.append(kvp("time", str));
        }
        if (choice == 6)
        {
            int num;
            bsoncxx::builder::basic::document another_builder{};
            cout << "Please input the number of the labels..." << endl;
            cin >> num;
            for (int j=0; j<num; j++)
            {
                cout << "Please input a label..." << endl;
                cin >> str;
                string str2;
                stringstream s;
                s << j;
                s >> str2;
                another_builder.append(kvp(str2, str));
            }
            basic_builder.append(kvp("label", another_builder));
        }
        if (choice == 7)
        {
            cout << "Please input introduction..." << endl;
            cin >> str;
            basic_builder.append(kvp("introduction", str));
        }
        if (choice == 8)
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
    return basic_builder.extract();
}

void Administrator::add_book(){
    bsoncxx::document::value document = get_book();
    shop->addItem(document);
}
//修改信息
void Administrator::modify_book(){
    bsoncxx::document::value document = find_book();
    mongocxx::cursor found = sc->search(document);
    mongocxx::cursor found2 = sc->search(document);
    bsoncxx::document::value book = check_book(found, found2);
    bsoncxx::document::value newbook = get_book();
    shop->editItem(book.view()["_id"].get_oid().value.to_string(), newbook);
    cout<<"haha"<<endl;
}
//审核归还
void Administrator::check_giveback(){
    mongocxx::cursor list = rc->getReturnList();
    mongocxx::cursor list2 = rc->getReturnList();
    bsoncxx::document::value book = check_book(list, list2);
    rc->commitReturn(book.view()["id"].get_utf8().value.to_string());
}

void Administrator::help(){
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Welcome back!" << endl;
    cout << "You are an administrator." << endl;
    cout << "You can manage our library's operation using the following statements." << endl;
    cout << "0) quit: Log out." << endl;
    cout << "1) add: Add books to our database." << endl;
    cout << "2) modify: Modify books' information in our database." << endl;
    cout << "3) check: Check the return-request list." << endl;
    cout << "------------------------------------------------------------------------------" << endl;
}

void Administrator::Main(){
    cout<<"user_id is:"<<this->getid()<<endl;
    cout<<"user_name is"<<this->getName()<<endl;
    cout<<"user_identity is"<<this->getIdentity()<<endl;
    cout<<"Please input orders...(input 'help' to see help page)" << endl;
    string str;
    while (cin >> str)
    {
        if (str == "quit" || str == "0" || str == "0)") break;
        if (str == "add" || str == "1" || str == "1)") add_book();
        if (str == "modify" || str == "2" || str == "2)") modify_book();
        if (str == "check" || str == "3" || str == "3)") check_giveback();
        if (str == "help") help();
        cout<<"Please input orders...(input 'help' to see help page)" << endl;
    }
    cout << "Your work helps make us better and better." << endl;
    cout << "Goodbye!" << endl;
}
