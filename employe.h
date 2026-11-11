#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QList>
#include <QSqlQueryModel>

class Employe
{
private:
    QString id, nom, prenom, telephone, mail, adresse;
    QString dateEmbauche, poste, dateNaissance;
    QString motDePasse, questionSecrete, reponse;

public:
    Employe();
    Employe(const QString &id, const QString &nom, const QString &prenom,
            const QString &telephone, const QString &mail, const QString &adresse,
            const QString &dateEmbauche, const QString &poste,
            const QString &dateNaissance, const QString &motDePasse,
            const QString &questionSecrete, const QString &reponse);

    QString getId() const              { return id; }
    QString getNom() const             { return nom; }
    QString getPrenom() const          { return prenom; }
    QString getTelephone() const       { return telephone; }
    QString getMail() const            { return mail; }
    QString getAdresse() const         { return adresse; }
    QString getDateEmbauche() const    { return dateEmbauche; }
    QString getPoste() const           { return poste; }
    QString getDateNaissance() const   { return dateNaissance; }
    QString getMotDePasse() const      { return motDePasse; }
    QString getQuestionSecrete() const { return questionSecrete; }
    QString getReponse() const         { return reponse; }

    void setId(const QString &v)              { id = v; }
    void setNom(const QString &v)             { nom = v; }
    void setPrenom(const QString &v)          { prenom = v; }
    void setTelephone(const QString &v)       { telephone = v; }
    void setMail(const QString &v)            { mail = v; }
    void setAdresse(const QString &v)         { adresse = v; }
    void setDateEmbauche(const QString &v)    { dateEmbauche = v; }
    void setPoste(const QString &v)           { poste = v; }
    void setDateNaissance(const QString &v)   { dateNaissance = v; }
    void setMotDePasse(const QString &v)      { motDePasse = v; }
    void setQuestionSecrete(const QString &v) { questionSecrete = v; }
    void setReponse(const QString &v)         { reponse = v; }

    bool ajouter();
    bool modifier();
    static bool supprimer(const QString &id);
    QSqlQueryModel* afficher();

    static QList<Employe> chargerTous();
    static QString genererId();
    static bool idExiste(const QString &id);
};

#endif // EMPLOYE_H