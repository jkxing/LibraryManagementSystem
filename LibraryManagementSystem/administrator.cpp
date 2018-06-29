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
        cout << endl;
        if (choosed[choice])
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
    return basic_builder.extract();
}

bsoncxx::document::value check_book(mongocxx::cursor& list){
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
        auto iter1 = list.begin();
        auto iter2 = list.end();
        int num = 0;
        while (iter1 != iter2)
        {
            iter1++;
            num++;
        }
        string* bookname = new string[num];
        string* authorname = new string[num];
        string* ISBN = new string[num];
        int i = 0;
        bsoncxx::document::element tmp;
        for (auto doc : list)
        {
            cout << endl;
            tmp = doc["bookname"];
            bookname[i] = tmp.get_utf8().value.to_string();
            tmp = doc["authorname"];
            authorname[i] = tmp.get_utf8().value.to_string();
            tmp = doc["ISBN"];
            ISBN[i] = tmp.get_utf8().value.to_string();
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
            cout << "Search failed." << endl;
            bsoncxx::document::value key = builder
                    << "wtf" << "wtf"
                    << bsoncxx::builder::stream::finalize;
            return db->get("Item", key);
        }
        i--;
        bsoncxx::document::value key = builder
                << "bookname" << bookname[i]
                << "authorname" << authorname[i]
                << "ISBN" << ISBN[i]
                << bsoncxx::builder::stream::finalize;
        return db->get("Item", key);
    }
}

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
    bsoncxx::document::value document = find_book();
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
            cout << "Search failed." << endl;
            return;
        }
        else
        {
            i--;
            //删除
        }
    }
}

void Administrator::modify_book(){
    bsoncxx::document::value document = find_book();
    mongocxx::cursor found = sc->search(document);
    bsoncxx::document::value book = check_book(found);
    shop->editItem(book.view()["id"].get_utf8().value.to_string(), document);
}
//审核借阅
void Administrator::check_borrow(const string &user_id){
    mongocxx::cursor list = rc->getBorrowList(user_id);
    bsoncxx::document::value book = check_book(list);
    //确认
};
//审核归还
void Administrator::check_giveback(){
    mongocxx::cursor list = rc->getReturnList();
    bsoncxx::document::value book = check_book(list);
    rc->commitReturn(book.view()["id"].get_utf8().value.to_string());
};

void Administrator::help(){
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "Welcome back!" << endl;
    cout << "You are an administrator." << endl;
    cout << "You can manage our library's operation using the following statements." << endl;
    cout << "0) quit: Log out." << endl;
    cout << "1) add a book: Add books to our database." << endl;
    cout << "2) delete a book: Delete books from our database." << endl;
    cout << "3) modify a book: Modify books' information in our database." << endl;
    cout << "4) check borrow: Check the borrow-request list." << endl;
    cout << "5) check return: Check the return-request list." << endl;
    cout << "------------------------------------------------------------------------------" << endl;
}

void Administrator::main(){
    cout<<"user_id is:"<<this->getid()<<endl;
    cout<<"user_name is"<<this->getName()<<endl;
    cout<<"user_identity is"<<this->getIdentity()<<endl;
    cout<<"Please input orders...(input 'help' to see help page)" << endl;
    string str;
    while (cin >> str)
    {
        if (str == "quit" || str == "0" || str == "0)") break;
        if (str == "add a book" || str == "1" || str == "1)") add_book();
        if (str == "delete a book" || str == "2" || str == "2)") delete_book();
        if (str == "modify a book" || str == "3" || str == "3)") modify_book();
        if (str == "check borrow" || str == "4" || str == "4)")
        {
            string id;
            cout << "Please input your user id..." << endl;
            cin >> id;
            check_borrow(id);
        }
        if (str == "check return" || str == "5" || str == "5)") check_giveback();
        cout<<"Please input orders...(input 'help' to see help page)" << endl;
    }
    cout << "Your work helps make us better and better." << endl;
    cout << "Goodbye!" << endl;
}
