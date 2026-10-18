#pragma once

#include <QColor>
#include <QDate>
#include <QSqlQueryModel>
#include <QString>

enum class Health { Sain, EnSoin, Urgent };

QString healthText(Health h);
QColor  healthColor(Health h);
QString ageText(int years);

class Animal {
public:
    Animal();
    Animal(int id, const QString &nom, const QString &espece, const QString &race,
           const QDate &dateNaissance, const QString &puce, const QString &vaccinal,
           const QString &proprietaire, const QString &telephone, Health sante);

    int getId() const { return m_id; }
    QString getNom() const { return m_nom; }
    QString getEspece() const { return m_espece; }
    QString getRace() const { return m_race; }
    QDate getDateNaissance() const { return m_dateNaissance; }
    int getAge() const;
    QString getPuce() const { return m_puce; }
    QString getVaccinal() const { return m_vaccinal; }
    QString getProprietaire() const { return m_proprietaire; }
    QString getTelephone() const { return m_telephone; }
    Health getSante() const { return m_sante; }

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel *trierParDateNaissance(bool ascendant = true);

    static bool ensureTable();
    static Animal trouverParId(int id);

private:
    int     m_id = 0;
    QString m_nom;
    QString m_espece = QStringLiteral("Chien");
    QString m_race;
    QDate   m_dateNaissance;
    QString m_puce;
    QString m_vaccinal = QStringLiteral("À jour");
    QString m_proprietaire;
    QString m_telephone;
    Health  m_sante = Health::Sain;
};

