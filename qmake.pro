QT       += widgets sql printsupport

TEMPLATE = app
TARGET = Pawche
CONFIG += c++17

SOURCES += \
    main.cpp \
    animal.cpp \
    connection.cpp \
    mainwindow.cpp

HEADERS += \
    animal.h \
    connection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

win32: CONFIG += windows
