TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ai.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    connect_four.h

