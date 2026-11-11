QT       += core gui widgets printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# libqrencode (vcpkg - MinGW static)
LIBS += -L"C:/Users/ASUS/Desktop/Qt/GestionCommandes/vcpkg/installed/x64-mingw-static/lib" -lqrencode
INCLUDEPATH += "C:/Users/ASUS/Desktop/Qt/GestionCommandes/vcpkg/installed/x64-mingw-static/include"

SOURCES += \
    Petcarecenter.cpp \
    connection.cpp \
    employe.cpp \
    main.cpp

HEADERS += \
    Petcarecenter.h \
    connection.h \
    employe.h

FORMS += \
    Petcarecenter.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target