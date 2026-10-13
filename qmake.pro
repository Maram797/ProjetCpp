QT       += widgets sql

TEMPLATE = app
TARGET = Pawche
CONFIG += c++17

SOURCES += \
    main.cpp \
    animal.cpp \
    connection.cpp

HEADERS += \
    animal.h \
    connection.h

FORMS += \
    mainwindow.ui

win32: CONFIG += windows
