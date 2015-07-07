TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game_match.cpp \
    ai.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    game_match.h \
    ai.h \
    connect_four.h

DISTFILES += \
    LICENSE_1_0.txt

