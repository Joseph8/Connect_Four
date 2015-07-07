TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ai_test.cpp

include(deployment.pri)
qtcAddDeployment()

include(../ConnectFour/deployment.pri)

HEADERS += \
    catch.hpp

