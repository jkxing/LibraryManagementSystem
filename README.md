
#图书管理系统项目文档
##组员
邢健开 2017011337
周炫柏 2017011460
张可真 2017011432
尹涵 8字班
##项目需求
###Qt框架
Qt 5.10
Qt Creator 4.6
###编译器
mingw53_32
###mongo数据库：
 客户端地址https://www.mongodb.com/download-center#community
 使用方法：https://docs.mongodb.com/manual/tutorial/install-mongodb-enterprise-on-windows/
采取默认端口27017即可
 c++驱动：在附件中，在win10 x86/64下应该可运行
###boost库：
 在附件中
##使用方法
###命令行界面
在项目-Run-Command line arguments中，加入-m g

![](./_image/2018-07-01-16-38-02.jpg)
####如可以运行mongoDB数据库
1.在LibraryManagementSystem.pro中，取消注释DEFINES += __Database
![](./_image/2018-07-01-16-39-29.jpg)
2.运行
3.注册 
用户名密码长度不小于6
如果用户名为adminnn，身份为管理员，否则为读者
4.登录管理员界面
可添加书籍
可编辑书籍信息
5.退出
6.登录用户界面
可搜索书籍（可以不输入，但输入的需要和书籍完全相同）
双击条目可借书，默认借书时间30天
点击借书列表可查看借书列表
双击条目可还书
7.回到管理员界面
可确认还书
####如果无法运行数据库
可用reader用户名登录读者界面，admin登录管理员界面，密码不用填
无法显示数据，只有界面
###命令行
在项目-Run-Command line arguments中，加入-m c
可按提示进行注册，登录，退出等操作
读者界面使用指南（来源：周炫柏）：
User类主要为Reader类提供一系列接口，具体功能大部分在Reader中实现。
User类中有一个重要的函数search，是Reader类借书还书操作的底层实现函数。它通过接收用户输入的信息（书名/作者名/标签），然后调用Searcher类中的Searcher::search函数，找到与这些信息相关的书籍并以cursor形式返回出来，User::search再将返回出来的书籍信息全部打印到屏幕上，让用户继续选择具体是哪一本书，然后根据用户的选择将对应书籍的id返回给上层函数。
Reader类定义了读者可以进行的一系列操作，包括阅读帮助界面（help函数），借书操作（borrow函数），还书操作（giveback函数），更改密码（changepassword函数），以及退出系统。借书、还书交由rendingcontrol类进行，分别调用newRendRequest函数和newReturnRequest函数；更改密码交由usercontrol类进行，调用updateUserInfo函数。故Reader类为读者与系统内核交互的中间媒介。
管理员界面使用指南（来源：张可真）：
Administrator类
以管理员身份登录后，首先进入主界面：
	Please input orders...(input 'help' to see help page)
输入help可查看帮助页面，具体功能如下：
1）添加书籍
指令：add 或 1
进入输入书籍信息的界面，列出一些书籍信息的可选项，输入
选项前的数字可输入相应信息，选择that's all项可结束编辑。
2）修改书籍信息
指令：modify 或 2
仍然进入输入书籍信息的界面，输入信息搜索制定书籍，之后
会列出搜索到的书籍，输入选项前的数字进行选择（若搜到的
均不是想要的可输入0），之后可进行书籍修改信息的输入，方
法同1）。
3）审核还书申请
指令：check 或 3
首先会列出正在等待审核的还书申请，输入选项前的数字进行
选择（输入0为不选）。
4）退出
指令：quit 或 0
每进行一次操作之后都会自动回到主界面，只有选择退出后可
以结束程序。
同样，如果没有数据库，就无法显示数据
##文档
[在线文档](http://doc.jkxing.cn/LibraryManagementSystem) ，由Doxygen生成
文档中包含UML图和各个类的接口

##分工(代码量)
邢健开：服务端，数据库，图形界面，命令行登录界面（约80KB）
张可真：命令行管理员界面（约12KB）
周炫柏：命令行读者界面，抽象用户类（约6KB)
尹涵：中途退出，没有贡献- -||（0KB）
