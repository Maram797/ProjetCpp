#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>

struct Employe
{
    QString id;
    QString nom;
    QString prenom;
    QString telephone;
    QString mail;
    QString adresse;
    QString dateEmbauche;
    QString poste;
    QString dateNaissance;
    QString motDePasse;
    QString questionSecrete;
    QString reponse;
};

#endif // EMPLOYE_H