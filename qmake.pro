QT += core gui widgets printsupport

CONFIG += c++17

SOURCES += \
    main.cpp \
    gestionrendezvous.cpp

HEADERS += \
    gestionrendezvous.h

FORMS += \
    gestionrendezvous.ui

# Decommente si tu as un fichier resources.qrc dans le dossier
# RESOURCES += resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
