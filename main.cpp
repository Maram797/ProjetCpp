#include "gestionrendezvous.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GestionRendezvous w;
    w.show();
    return a.exec();
}