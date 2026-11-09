QT       += widgets sql printsupport

TEMPLATE = app
TARGET = Pawche
CONFIG += c++17

SOURCES += \
    main.cpp \
    animal.cpp \
    connection.cpp \
    Petcarecenter.cpp

HEADERS += \
    animal.h \
    connection.h \
    Petcarecenter.h

FORMS += \
    Petcarecenter.ui

RESOURCES += \
    resources.qrc

win32: CONFIG += windows
