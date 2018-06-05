QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
INCLUDEPATH += boost\include\boost-1_67
LIBS += -L"mongo-cxx-driver/lib" -lmongocxx -lbsoncxx
LIBS += -L"boost\lib"

SOURCES += \
        main.cpp \
    abstractapp.cpp \
    consoleapp.cpp \
    user.cpp \
    books.cpp \
    database.cpp \
    rendingcontrol.cpp \
    searcher.cpp \
    shop.cpp \
    usercontrol.cpp \
    const.cpp

HEADERS += \
    abstractapp.h \
    consoleapp.h \
    user.h \
    books.h \
    database.h \
    shop.h \
    const.h \
    rendingcontrol.h \
    searcher.h \
    usercontrol.h

