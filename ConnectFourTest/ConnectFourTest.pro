TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#TARGET = ConnectFourTest

CONFIG += testcase

INCLUDEPATH += $$PWD/../ConnectFourLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ConnectFourLib/release/ -lConnectFourLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ConnectFourLib/debug/ -lConnectFourLib

SOURCES += \
    ai_test.cpp

#include(deployment.pri)
#qtcAddDeployment()

#include(../ConnectFour/deployment.pri)

HEADERS += \
    catch.hpp
