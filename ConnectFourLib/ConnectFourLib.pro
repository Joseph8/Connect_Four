#-------------------------------------------------
#
# Project created by QtCreator 2015-07-19T17:50:08
#
#-------------------------------------------------

QT       -= gui

TARGET = ConnectFourLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ../ConnectFour/ai.cpp \
    ../ConnectFour/game_match.cpp \
    ../ConnectFour/main.cpp

HEADERS += ../ConnectFour/ai.h \
    ../ConnectFour/game_match.h \
    ../ConnectFour/connect_four.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
