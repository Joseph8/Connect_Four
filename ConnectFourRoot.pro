TEMPLATE = subdirs
CONFIG += c++11
CONFIG += ordered

SUBDIRS += \
    ConnectFour \
#if the following lines are commented out the tests will not be built
    ConnectFourTest \
    ConnectFourLib
ConnectFourLib.depends = ConnectFour
ConnectFourTest.depends = ConnectFourLib
