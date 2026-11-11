#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QVariant>

Employe::Employe() {}

Employe::Employe(const QString &id, const QString &nom, const QString &prenom,
                 const QString &telephone, const QString &mail, const QString &adresse,
                 const QString &dateEmbauche, const QString &poste,
                 const QString &dateNaissance, const QString &motDePasse,
                 const QString &questionSecrete, const QString &reponse)
    : id(id), nom(nom), prenom(prenom), telephone(telephone), mail(mail),
    adresse(adresse), dateEmbauche(dateEmbauche), poste(poste),
    dateNaissance(dateNaissance), motDePasse(motDePasse),
    questionSecrete(questionSecrete), reponse(reponse) {}

bool Employe::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, TELEPHONE, MAIL, ADRESSE, DATE_EMBAUCHE, POSTE, DATE_NAISSANCE, MOT_DE_PASSE, QUESTION_SECRETE, REPONSE) "
                  "VALUES (:id, :nom, :prenom, :telephone, :mail, :adresse, :dateEmbauche, :poste, :dateNaissance, :motDePasse, :questionSecrete, :reponse)");
    query.bindValue(":id", id); query.bindValue(":nom", nom); query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone); query.bindValue(":mail", mail); query.bindValue(":adresse", adresse);
    query.bindValue(":dateEmbauche", dateEmbauche); query.bindValue(":poste", poste); query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":motDePasse", motDePasse); query.bindValue(":questionSecrete", questionSecrete); query.bindValue(":reponse", reponse);
    return query.exec();
}

bool Employe::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET NOM=:nom, PRENOM=:prenom, TELEPHONE=:telephone, MAIL=:mail, ADRESSE=:adresse, DATE_EMBAUCHE=:dateEmbauche, POSTE=:poste, DATE_NAISSANCE=:dateNaissance, MOT_DE_PASSE=:motDePasse, QUESTION_SECRETE=:questionSecrete, REPONSE=:reponse WHERE ID=:id");
    query.bindValue(":nom", nom); query.bindValue(":prenom", prenom); query.bindValue(":telephone", telephone);
    query.bindValue(":mail", mail); query.bindValue(":adresse", adresse); query.bindValue(":dateEmbauche", dateEmbauche);
    query.bindValue(":poste", poste); query.bindValue(":dateNaissance", dateNaissance); query.bindValue(":motDePasse", motDePasse);
    query.bindValue(":questionSecrete", questionSecrete); query.bindValue(":reponse", reponse); query.bindValue(":id", id);
    return query.exec();
}

bool Employe::supprimer(const QString &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID, NOM, PRENOM, TELEPHONE, MAIL FROM EMPLOYES");
    return model;
}

bool Employe::idExiste(const QString &id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) return query.value(0).toInt() > 0;
    return false;
}

QList<Employe> Employe::chargerTous() {
    QList<Employe> liste;
    QSqlQuery query("SELECT * FROM EMPLOYES");
    while (query.next()) {
        Employe e;
        e.setId(query.value("ID").toString()); e.setNom(query.value("NOM").toString());
        e.setPrenom(query.value("PRENOM").toString()); e.setTelephone(query.value("TELEPHONE").toString());
        e.setMail(query.value("MAIL").toString()); e.setAdresse(query.value("ADRESSE").toString());
        e.setDateEmbauche(query.value("DATE_EMBAUCHE").toString()); e.setPoste(query.value("POSTE").toString());
        e.setDateNaissance(query.value("DATE_NAISSANCE").toString()); e.setMotDePasse(query.value("MOT_DE_PASSE").toString());
        e.setQuestionSecrete(query.value("QUESTION_SECRETE").toString()); e.setReponse(query.value("REPONSE").toString());
        liste.append(e);
    }
    return liste;
}

QString Employe::genererId() {
    QString id;
    do { id = QString("EMP-%1").arg(QRandomGenerator::global()->bounded(10000, 100000)); }
    while (idExiste(id));
    return id;
}