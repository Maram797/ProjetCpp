QT       += widgets

TEMPLATE = app
TARGET = Pawche
CONFIG += c++17

SOURCES += \
    main.cpp \
    animal.cpp

HEADERS += \
    animal.h

FORMS += \
    mainwindow.ui

win32: CONFIG += windows
