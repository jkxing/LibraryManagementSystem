#include "Administrator.h"
#include <sstream>
extern Shop* shop;
extern Searcher* sc;
extern RendControl* rc;
extern Database* db;
//输入搜索一本书的信息
bsoncxx::document::value find_book(){
    string str;
    int choice;
    string info[6] = {"书名", "作者", "译者", "出版社",
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
            basic_builder.append(kvp("书名", str));
        }
        if (choice == 2)
        {
            cout << "Please input the name of the author..." << endl;
            cin >> str;
            basic_builder.append(kvp("作者", str));
        }
        if (choice == 3)
        {
            cin >> str;
            cout << "Please input the name(s) of the translator(s)..." << endl;
            cin >> str;
            basic_builder.append(kvp("译者", str));
        }
        if (choice == 4)
        {
            cout << "Please input the press..." << endl;
            cin >> str;
            basic_builder.append(kvp("出版社", str));
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
//从列表中选择一本书
bsoncxx::document::value check_book(vector<bsoncxx::document::value> list){
    auto builder = bsoncxx::builder::stream::document{};
    if(list.begin() == list.end())
    {
        cout << "No request is waiting for confirmation yet." << endl;
        return document().extract();
    }
    else
    {
        string* bookname = new string[list.size()+1];
        string* authorname = new string[list.size()+1];
        string* ISBN = new string[list.size()+1];
        string* press = new string[list.size()+1];
        string* time = new string[list.size()+1];
        string* introduction = new string[list.size()+1];
        string* translator = new string[list.size()+1];
        for (int i=1; i<(int)list.size(); i++)
        {
            bookname[i] = "";
            authorname[i] = "";
            ISBN[i] = "";
            press[i] = "";
        }
        int i = 0;
        for (auto doc1 : list)
        {
            auto doc = doc1.view();
            i++;
            cout << i << "." << endl;
            if (doc.find("书名") != doc.end())
            {
                bookname[i] = doc["书名"].get_utf8().value.to_string();
                cout << bookname[i] << endl;
            }
            if (doc.find("作者") != doc.end())
            {
                authorname[i] = doc["作者"].get_utf8().value.to_string();
                cout << authorname[i] << endl;
            }
            if (doc.find("译者") != doc.end())
            {
                translator[i] = doc["译者"].get_utf8().value.to_string();
                cout << translator[i] << endl;
            }
            if (doc.find("出版社") != doc.end())
            {
                press[i] = doc["出版社"].get_utf8().value.to_string();
                cout << press[i] << endl;
            }
            if (doc.find("出版时间") != doc.end())
            {
                time[i] = doc["出版时间"].get_utf8().value.to_string();
                cout << time[i] << endl;
            }
            if (doc.find("ISBN") != doc.end())
            {
                ISBN[i] = doc["ISBN"].get_utf8().value.to_string();
                cout << ISBN[i] << endl;
            }
            if (doc.find("编辑推荐") != doc.end())
            {
                introduction[i] = doc["编辑推荐"].get_utf8().value.to_string();
                cout << introduction[i] << endl;
            }
        }
        cout << endl;
        cout << "Choose one... (0 for quit)" << endl;
        cin >> i;
        while (!(i >= 0 && i <= (int)list.size()))
        {
            cout << "Invalid number." << endl;
            cout << "Please choose again..." << endl;
            cin >> i;
        }
        if (i == 0)
        {
            cout << "Search failed." << endl;
            return document().extract();
        }
        builder.clear();
        if (ISBN[i] != "")
        {
            builder << "ISBN" << ISBN[i];
        }
        if (bookname[i] != "")
        {
            builder << "书名" << bookname[i];
        }
        if (authorname[i] != "")
        {
            builder << "作者" << authorname[i];
        }
        if (authorname[i] != "")
        {
            builder << "出版社" << press[i];
        }
        if (time[i] != "")
        {
            builder << "出版时间" << time[i];
        }
        if (translator[i] != "")
        {
            builder << "译者" << translator[i];
        }
        if (introduction[i] != "")
        {
            builder << "编辑推荐" << introduction[i];
        }
        bsoncxx::document::value key = builder.extract();
        return db->get("Item", key.view());
    }
}
//新建一本书
bsoncxx::document::value get_book(){
    string str;
    int choice;
    string info[9] = {"书名", "作者", "译者", "出版社",
                    "出版时间", "标签", "编辑推荐", "ISBN", "that's all"};
    bool choosed[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    //用于保存书籍信息
    bsoncxx::builder::basic::document basic_builder{};
    //用于保存标签
    bsoncxx::builder::basic::document another_builder{};

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
            basic_builder.append(kvp("书名", str));
        }
        if (choice == 2)
        {
            cout << "Please input the name of the author..." << endl;
            cin >> str;
            basic_builder.append(kvp("作者", str));
        }
        if (choice == 3)
        {
            cin >> str;
            cout << "Please input the name(s) of the translator(s)..." << endl;
            cin >> str;
            basic_builder.append(kvp("译者", str));
        }
        if (choice == 4)
        {
            cout << "Please input the press..." << endl;
            cin >> str;
            basic_builder.append(kvp("出版社", str));
        }
        if (choice == 5)
        {
            cout << "Please input publication time..." << endl;
            cin >> str;
            basic_builder.append(kvp("出版时间", str));
        }
        if (choice == 6)
        {
            int num;
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
        }
        if (choice == 7)
        {
            cout << "Please input introduction..." << endl;
            cin >> str;
            basic_builder.append(kvp("编辑推荐", str));
        }
        if (choice == 8)
        {
            cout << "Please input the ISBN number..." << endl;
            cin >> str;
            basic_builder.append(kvp("ISBN", str));
        }
        choosed[choice] = true;
        cout << "What infomation do you have about the book?" << endl;
        for (int i = 0; i < 9; i++)
            cout << (i+1) << ". " << info[i] << endl;
    }
    //basic_builder.append(kvp("标签", another_builder));
    return basic_builder.extract();
}
//添加书
void Administrator::add_book(){
    bsoncxx::document::value document = get_book();
    shop->addItem(document);
}
//修改信息
void Administrator::modify_book(){
    cout<<"finish modify_0"<<endl;
    bsoncxx::document::value document = find_book();
    cout<<"finish modify_0.5"<<endl;
    vector<bsoncxx::document::value> found = sc->search(document);
    cout<<"finish modify_1"<<endl;
    bsoncxx::document::value book = check_book(found);
    cout<<"finish modify_1.5"<<endl;
    if (book.view() == bsoncxx::document::view{}) return;
    bsoncxx::document::value newbook = get_book();
    cout<<"finish modify_2"<<endl;
    cout << book.view()["_id"].get_oid().value.to_string() << endl;
    string tmp = book.view()["_id"].get_oid().value.to_string();
    cout << bsoncxx::to_json(newbook) << endl;
    shop->editItem(tmp, newbook.view());
    cout<<"haha"<<endl;
}
//审核归还
void Administrator::check_giveback(){
    vector<bsoncxx::document::value> list = rc->getReturnList();
    bsoncxx::document::value book = check_book(list);
    if (book.view() == bsoncxx::document::view{}) return;
    rc->commitReturn(book.view()["id"].get_utf8().value.to_string());
}
//帮助页面
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
//主界面
void Administrator::Main(){
    cout<<"user_id is:"<<this->getid()<<endl;
    cout<<"user_name is"<<this->getName()<<endl;
    cout<<"user_identity is"<<this->getIdentity()<<endl;
    cout<<"Please input orders...(input 'help' to see help page)" << endl;
    string str;
    while (cin >> str)
    {
        //退出
        if (str == "quit" || str == "0" || str == "0)") break;
        //添加书籍
        if (str == "add" || str == "1" || str == "1)") add_book();
        //修改书籍信息
        if (str == "modify" || str == "2" || str == "2)") modify_book();
        //审核还书申请
        if (str == "check" || str == "3" || str == "3)") check_giveback();
        //帮助页面
        if (str == "help") help();
        cout<<"Please input orders...(input 'help' to see help page)" << endl;
    }
    cout << "Your work helps make us better and better." << endl;
    cout << "Goodbye!" << endl;
}
