QT+=widgets
CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += resources_big
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += __Database
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += mongo-cxx-driver/include/mongocxx/v_noabi
INCLUDEPATH += mongo-cxx-driver/include/libmongoc-1.0
INCLUDEPATH += mongo-cxx-driver/include/bsoncxx/v_noabi
INCLUDEPATH += mongo-cxx-driver/include/libbson-1.0
INCLUDEPATH += boost/include/boost-1_67
LIBS += -L"mongo-cxx-driver/lib" -lmongocxx -lbsoncxx


SOURCES += \
    main.cpp \
    abstractapp.cpp \
    consoleapp.cpp \
    user.cpp \
    database.cpp \
    rendingcontrol.cpp \
    searcher.cpp \
    shop.cpp \
    usercontrol.cpp \
    const.cpp \
    reader.cpp \
    administrator.cpp \
    date.cpp \
    guiapp.cpp \
    logindialog.cpp \
    dialog.cpp \
    usergui.cpp \
    searchui.cpp \
    admingui.cpp \
    editdialog.cpp \
    confirmdialog.cpp \
    addbookdialog.cpp

HEADERS += \
    abstractapp.h \
    consoleapp.h \
    user.h \
    database.h \
    shop.h \
    const.h \
    rendingcontrol.h \
    searcher.h \
    date.h \
    usercontrol.h \
    Administrator.h \
    Reader.h \
    guiapp.h \
    logindialog.h \
    dialog.h \
    usergui.h \
    searchui.h \
    admingui.h \
    editdialog.h \
    confirmdialog.h \
    addbookdialog.h

DISTFILES +=

FORMS += \
    guiapp.ui \
    logindialog.ui \
    dialog.ui \
    usergui.ui \
    searchui.ui \
    admingui.ui \
    editdialog.ui \
    confirmdialog.ui \
    addbookdialog.ui

RESOURCES += \
    res.qrc

