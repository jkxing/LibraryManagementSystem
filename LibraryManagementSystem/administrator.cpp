#include "Administrator.h"
#include <QDebug>
extern Shop* shop;
extern Searcher* sc;
extern RendControl* rc;

//输入搜索一本书的信息
bsoncxx::document::value find_book(){                  
    string str;
    int choice;
    string info[6] = {"书名", "作者", "译者", "出版社",
                    "ISBN", "that's all"};
    bool choosed[6] = {0, 0, 0, 0, 0, 0};//防止重复输入
    bsoncxx::builder::basic::document basic_builder{};

    qDebug() << "Let's find the book first.";
    qDebug() << "What infomation do you have about the book?";
    for (int i = 0; i < 6; i++)
        qDebug() << (i+1) << ". " << QString::fromStdString(info[i]);
    while (cin >> choice)
    {
        if (choice == 6) break;
        if (choice >= 7 || choice <= 0)
        {
            qDebug() << "Invalid number. Choose again.";
            continue;
        }
        if (choosed[choice])
        {
            qDebug() << "You have input this already. Choose again.";
            continue;
        }
        if (choice == 1)
        {
            qDebug() << "Please input the name of the book...";
            cin >> str;
            basic_builder.append(kvp("书名", str));
        }
        if (choice == 2)
        {
            qDebug() << "Please input the name of the author...";
            cin >> str;
            basic_builder.append(kvp("作者", str));
        }
        if (choice == 3)
        {
            cin >> str;
            qDebug() << "Please input the name(s) of the translator(s)...";
            cin >> str;
            basic_builder.append(kvp("译者", str));
        }
        if (choice == 4)
        {
            qDebug() << "Please input the press...";
            cin >> str;
            basic_builder.append(kvp("出版社", str));
        }
        if (choice == 5)
        {
            qDebug() << "Please input the ISBN number...";
            cin >> str;
            basic_builder.append(kvp("ISBN", str));
        }
        choosed[choice] = true;
        qDebug() << "What infomation do you have about the book?";
        for (int i = 0; i < 6; i++)
            qDebug() << (i+1) << ". " << QString::fromStdString(info[i]);
    }
    return basic_builder.extract();
}
//从列表中选择一本书
bsoncxx::document::value check_book(vector<bsoncxx::document::value> list, bool borrow, bool giveback){
    auto builder = bsoncxx::builder::stream::document{};
    if(list.begin() == list.end())//列表为空
    {
        qDebug() << "No request is waiting for confirmation yet.";
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
        string* state = new string[list.size()+1];
        for (int i=1; i<(int)list.size(); i++)
        {
            bookname[i] = "";
            authorname[i] = "";
            ISBN[i] = "";
            press[i] = "";
            time[i] = "";
            introduction[i] = "";
            translator[i] = "";
            state[i] = "";
        }
        int i = 0;
        for (auto doc1 : list)
        {
            auto doc = doc1.view();
            i++;
            qDebug() << i << ".";
            if (doc.find("书名") != doc.end())
            {
                bookname[i] = doc["书名"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(bookname[i]);
            }
            if (doc.find("作者") != doc.end())
            {
                authorname[i] = doc["作者"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(authorname[i]);
            }
            if (doc.find("译者") != doc.end())
            {
                translator[i] = doc["译者"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(translator[i]);
            }
            if (doc.find("出版社") != doc.end())
            {
                press[i] = doc["出版社"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(press[i]);
            }
            if (doc.find("出版时间") != doc.end())
            {
                time[i] = doc["出版时间"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(time[i]);
            }
            if (doc.find("ISBN") != doc.end())
            {
                ISBN[i] = doc["ISBN"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(ISBN[i]);
            }
            if (doc.find("编辑推荐") != doc.end())
            {
                introduction[i] = doc["编辑推荐"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(introduction[i]);
            }
            if (doc.find("state") != doc.end())
            {
                state[i] = doc["state"].get_utf8().value.to_string();
                qDebug() << QString::fromStdString(state[i]);
            }
        }
        qDebug();
        qDebug() << "Choose one... (0 for quit)";
        cin >> i;
        while (!(i >= 0 && i <= (int)list.size()))
        {
            qDebug() << "Invalid number.";
            qDebug() << "Please choose again...";
            cin >> i;
        }
        if (i == 0)//取消操作
        {
            qDebug() << "Search failed.";
            return document().extract();
        }
        if (borrow)
        {
            while (state[i] != "checking")
            {
                qDebug() << "It is not to be lent.";
                qDebug() << "Please choose again...";
                cin >> i;
            }
        }
        if (giveback)
        {
            while (state[i] != "waiting")
            {
                qDebug() << "It is not to be returned.";
                qDebug() << "Please choose again...";
                cin >> i;
            }
        }
        return list[i-1];
    }
}
//新建一本书
bsoncxx::document::value get_book(){
    string str;
    int choice;
    string info[9] = {"书名", "作者", "译者", "出版社",
                    "出版时间", "标签", "编辑推荐", "ISBN", "that's all"};
    bool choosed[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};//防止重复输入
    //用于保存书籍信息
    bsoncxx::builder::basic::document basic_builder{};

    qDebug() << "What infomation do you have about the book?";
    for (int i = 0; i < 9; i++)
        qDebug() << (i+1) << ". " << QString::fromStdString(info[i]);
    while (cin >> choice)
    {
        if (choice == 9) break;
        if (choosed[choice])
        {
            qDebug() << "You have input this already. Choose again.";
            continue;
        }
        if (choice >= 10 || choice <= 0)
        {
            qDebug() << "Invalid number. Choose again.";
            continue;
        }
        if (choice == 1)
        {
            qDebug() << "Please input the name of the book...";
            cin >> str;
            basic_builder.append(kvp("书名", str));
        }
        if (choice == 2)
        {
            qDebug() << "Please input the name of the author...";
            cin >> str;
            basic_builder.append(kvp("作者", str));
        }
        if (choice == 3)
        {
            qDebug() << "Please input the name(s) of the translator(s)...";
            cin >> str;
            basic_builder.append(kvp("译者", str));
        }
        if (choice == 4)
        {
            qDebug() << "Please input the press...";
            cin >> str;
            basic_builder.append(kvp("出版社", str));
        }
        if (choice == 5)
        {
            qDebug() << "Please input publication time...";
            cin >> str;
            basic_builder.append(kvp("出版时间", str));
        }
        if (choice == 6)
        {
            int num;
            qDebug() << "Please input the number of the labels...";
            cin >> num;
            string* label = new string[num];
            for (int j=0; j<num; j++)
            {
                qDebug() << "Please input a label...";
                cin >> label[j];
            }            
            basic_builder.append(kvp("标签", [label, num](sub_array child) {
                for (int j=0; j<num; j++)
                {
                    child.append(label[j]);
                }
            }));
        }
        if (choice == 7)
        {
            qDebug() << "Please input introduction...";
            cin >> str;
            basic_builder.append(kvp("编辑推荐", str));
        }
        if (choice == 8)
        {
            qDebug() << "Please input the ISBN number...";
            cin >> str;
            basic_builder.append(kvp("ISBN", str));
        }
        choosed[choice] = true;
        qDebug() << "What infomation do you have about the book?";
        for (int i = 0; i < 9; i++)
            qDebug() << (i+1) << ". " << QString::fromStdString(info[i]);
    }
    return basic_builder.extract();
}
//添加书
void Administrator::add_book(){
    //编辑新书的信息
    bsoncxx::document::value document = get_book();
    //加入数据库
    shop->addItem(document);
}
//修改信息
void Administrator::modify_book(){
    qDebug()<<"finish modify_0"<<endl;
    bsoncxx::document::value document = find_book();
    qDebug()<<"finish modify_0.5"<<endl;
    vector<bsoncxx::document::value> found = sc->search(document);
    qDebug()<<"finish modify_1"<<endl;
    bsoncxx::document::value book = check_book(found, 0, 0);
    qDebug()<<"finish modify_1.5"<<endl;
    if (book.view() == bsoncxx::document::view{}) return;
    bsoncxx::document::value newbook = get_book();
    qDebug()<<"finish modify_2"<<endl;
    qDebug() << QString::fromStdString(book.view()["_id"].get_oid().value.to_string());
    string tmp = book.view()["_id"].get_oid().value.to_string();
    shop->editItem(tmp, newbook.view());
    qDebug()<<"#end of modify"<<endl;
}
//删除书籍
void Administrator::delete_book(){
    bsoncxx::document::value document = find_book();
    vector<bsoncxx::document::value> found = sc->search(document);
    bsoncxx::document::value book = check_book(found, 0, 0);
    if (book.view() == bsoncxx::document::view{}) return;
    string tmp = book.view()["_id"].get_oid().value.to_string();
    shop->removeItem(tmp);
}
//审核借书
void Administrator::check_borrow(){
    //获得等待审核的请求列表
    vector<bsoncxx::document::value> list = rc->getBorrowList();
    //选择一本书
    bsoncxx::document::value book = check_book(list, 1, 0);
    if (book.view() == bsoncxx::document::view{}) return;
    cout << book.view()["item_id"].get_oid().value.to_string() << endl;
    rc->commitBorrow(book.view()["_id"].get_oid().value.to_string());
    qDebug() << "Request commited.";
}
//审核归还
void Administrator::check_giveback(){
    //获得等待审核的请求列表
    vector<bsoncxx::document::value> list = rc->getReturnList();
    //选择一本书
    bsoncxx::document::value book = check_book(list, 0, 1);
    if (book.view() == bsoncxx::document::view{}) return;    
    rc->commitReturn(book.view()["item_id"].get_oid().value.to_string());
    qDebug() << "Request commited.";
}
//帮助页面
void Administrator::help(){
    qDebug() << "------------------------------------------------------------------------------";
    qDebug() << "You are an administrator.";
    qDebug() << "You can manage our library's operation using the following statements.";
    qDebug() << "0) quit: Log out.";
    qDebug() << "1) add: Add books to our database.";
    qDebug() << "2) modify: Modify books' information in our database.";
    qDebug() << "3) delete: Delete a book from our database.";
    qDebug() << "4) check: Check the return-request list.";
    qDebug() << "5) lend: Check the borrow-request list.";
    qDebug() << "------------------------------------------------------------------------------";
}
//主界面
void Administrator::Main(){
    qDebug() << "Welcome back!";
    qDebug() << "User identity: Administrator";
    qDebug();
    qDebug() << "Please input orders...(input 'help' to see help page)";
    string str;
    while (cin >> str)
    {
        //退出
        if (str == "quit" || str == "0" || str == "0)") break;
        //添加书籍
        if (str == "add" || str == "1" || str == "1)") add_book();
        //修改书籍信息
        if (str == "modify" || str == "2" || str == "2)") modify_book();
        //删除书籍
        if (str == "delete" || str == "3" || str == "3)") delete_book();
        //审核还书申请
        if (str == "check" || str == "4" || str == "4)") check_giveback();
        //审核借书申请
        if (str == "lend" || str == "5" || str == "5)") check_borrow();
        //帮助页面
        if (str == "help") help();
        qDebug()<<"Please input orders...(input 'help' to see help page)";
    }
    qDebug() << "Your work helps make us better and better.";
    qDebug() << "Goodbye!";
}
