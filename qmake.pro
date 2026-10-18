QT += core gui widgets printsupport sql

CONFIG += c++17 console

SOURCES += \
    main.cpp \
    connection.cpp \
    gestionrendezvous.cpp

HEADERS += \
    connection.h \
    gestionrendezvous.h

FORMS += \
    gestionrendezvous.ui

RESOURCES += resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
