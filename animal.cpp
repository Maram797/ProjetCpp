#include "animal.h"

#include <QDate>
#include <QRegularExpression>
#include <QSqlError>
#include <QSqlQuery>

QString healthText(Health h)
{
    switch (h) {
    case Health::Sain: return QStringLiteral("Sain");
    case Health::EnSoin: return QStringLiteral("En soin");
    case Health::Urgent: return QStringLiteral("Urgent");
    default: return {};
    }
}

QColor healthColor(Health h)
{
    switch (h) {
    case Health::Sain: return QColor("#287554");
    case Health::EnSoin: return QColor("#B8743F");
    case Health::Urgent: return QColor("#C2455F");
    default: return QColor("#000000");
    }
}

QString ageText(int years)
{
    if (years <= 0) return QStringLiteral("Moins d'un an");
    if (years == 1) return QStringLiteral("1 an");
    return QStringLiteral("%1 ans").arg(years);
}

static Health healthFromString(const QString &v)
{
    if (v.compare("Urgent", Qt::CaseInsensitive) == 0) return Health::Urgent;
    if (v.compare("En soin", Qt::CaseInsensitive) == 0) return Health::EnSoin;
    return Health::Sain;
}

static QString cleanPhone(const QString &p)
{
    QString x = p;
    x.remove(QRegularExpression("[^0-9]"));
    return x.isEmpty() ? QStringLiteral("0") : x;
}

static void headers(QSqlQueryModel *m)
{
    const QStringList h = {QObject::tr("ID"), QObject::tr("Nom"), QObject::tr("Espèce"), QObject::tr("Race"), QObject::tr("Date Naissance"), QObject::tr("Âge"), QObject::tr("Puce"), QObject::tr("Vaccination"), QObject::tr("Propriétaire"), QObject::tr("Téléphone"), QObject::tr("État Santé")};
    for (int i = 0; i < h.size(); ++i)
        m->setHeaderData(i, Qt::Horizontal, h[i]);
}

static QSqlQueryModel *model(const QString &q)
{
    auto *m = new QSqlQueryModel();
    m->setQuery(q);
    headers(m);
    return m;
}

Animal::Animal()
    : m_id(0)
    , m_espece(QStringLiteral("Chien"))
    , m_vaccinal(QStringLiteral("À jour"))
    , m_sante(Health::Sain)
{
    m_dateNaissance = QDate::currentDate();
}

Animal::Animal(int id, const QString &nom, const QString &espece, const QString &race,
               const QDate &dateNaissance, const QString &puce, const QString &vaccinal,
               const QString &proprietaire, const QString &telephone, Health sante)
    : m_id(id), m_nom(nom), m_espece(espece), m_race(race), m_dateNaissance(dateNaissance),
      m_puce(puce), m_vaccinal(vaccinal), m_proprietaire(proprietaire), m_telephone(telephone), m_sante(sante)
{}

int Animal::getAge() const
{
    if (!m_dateNaissance.isValid()) return 0;
    const QDate today = QDate::currentDate();
    int age = today.year() - m_dateNaissance.year();
    if (today < m_dateNaissance.addYears(age)) --age;
    return qMax(0, age);
}

bool Animal::ensureTable()
{
    QSqlQuery q;
    if (q.exec("CREATE TABLE animaux (id_animal NUMBER PRIMARY KEY, nom VARCHAR2(100) NOT NULL, race VARCHAR2(100) NOT NULL, sexe VARCHAR2(30) NOT NULL, date_naissance DATE NOT NULL, allergies VARCHAR2(200) NOT NULL, etat_sante VARCHAR2(30) NOT NULL, nom_proprietaire VARCHAR2(100) NOT NULL, telephone NUMBER NOT NULL, email VARCHAR2(100) NOT NULL, adresse VARCHAR2(200) NOT NULL, espece VARCHAR2(30), puce VARCHAR2(30), vaccinal VARCHAR2(30))"))
        return true;

    const QString err = q.lastError().text();
    if (err.contains("ORA-00955", Qt::CaseInsensitive) || err.contains("already exists", Qt::CaseInsensitive)) {
        const QStringList columns = {
            QStringLiteral("espece VARCHAR2(30)"),
            QStringLiteral("puce VARCHAR2(30)"),
            QStringLiteral("vaccinal VARCHAR2(30)")
        };
        for (const QString &c : columns) {
            QSqlQuery a;
            a.exec("ALTER TABLE animaux ADD (" + c + ")");
        }
        return true;
    }
    return false;
}

bool Animal::ajouter()
{
    QSqlQuery q;
    q.prepare("INSERT INTO animaux (id_animal, nom, race, sexe, date_naissance, allergies, etat_sante, nom_proprietaire, telephone, email, adresse, espece, puce, vaccinal) "
              "SELECT NVL(MAX(id_animal), 0) + 1, :nom, :race, 'Non renseigne', :date_naissance, 'Aucune', :etat_sante, :nom_proprietaire, TO_NUMBER(:telephone), 'inconnu@pawche.local', 'Non renseignee', :espece, :puce, :vaccinal FROM animaux");
    q.bindValue(":nom", m_nom);
    q.bindValue(":race", m_race);
    q.bindValue(":date_naissance", m_dateNaissance.isValid() ? m_dateNaissance : QDate::currentDate());
    q.bindValue(":etat_sante", healthText(m_sante));
    q.bindValue(":nom_proprietaire", m_proprietaire);
    q.bindValue(":telephone", cleanPhone(m_telephone));
    q.bindValue(":espece", m_espece);
    q.bindValue(":puce", m_puce);
    q.bindValue(":vaccinal", m_vaccinal);
    return q.exec();
}

bool Animal::modifier(int id)
{
    QSqlQuery q;
    q.prepare("UPDATE animaux SET nom = :nom, race = :race, date_naissance = :date_naissance, etat_sante = :etat_sante, nom_proprietaire = :nom_proprietaire, telephone = TO_NUMBER(:telephone), espece = :espece, puce = :puce, vaccinal = :vaccinal WHERE id_animal = :id");
    q.bindValue(":nom", m_nom);
    q.bindValue(":race", m_race);
    q.bindValue(":date_naissance", m_dateNaissance.isValid() ? m_dateNaissance : QDate::currentDate());
    q.bindValue(":etat_sante", healthText(m_sante));
    q.bindValue(":nom_proprietaire", m_proprietaire);
    q.bindValue(":telephone", cleanPhone(m_telephone));
    q.bindValue(":espece", m_espece);
    q.bindValue(":puce", m_puce);
    q.bindValue(":vaccinal", m_vaccinal);
    q.bindValue(":id", id);
    return q.exec();
}

bool Animal::supprimer(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM animaux WHERE id_animal = :id");
    q.bindValue(":id", id);
    return q.exec();
}

QSqlQueryModel *Animal::afficher()
{
    return model("SELECT id_animal, nom, espece, race, date_naissance, TRUNC(MONTHS_BETWEEN(SYSDATE, date_naissance) / 12) AS age, puce, vaccinal, nom_proprietaire, TO_CHAR(telephone), etat_sante FROM animaux ORDER BY nom ASC");
}

QSqlQueryModel *Animal::trierParDateNaissance(bool asc)
{
    const QString order = asc ? QStringLiteral("ASC") : QStringLiteral("DESC");
    return model(QStringLiteral("SELECT id_animal, nom, espece, race, date_naissance, TRUNC(MONTHS_BETWEEN(SYSDATE, date_naissance) / 12) AS age, puce, vaccinal, nom_proprietaire, TO_CHAR(telephone), etat_sante FROM animaux ORDER BY date_naissance ") + order);
}

Animal Animal::trouverParId(int id)
{
    QSqlQuery q;
    q.prepare("SELECT id_animal, nom, espece, race, date_naissance, puce, vaccinal, nom_proprietaire, TO_CHAR(telephone), etat_sante FROM animaux WHERE id_animal = :id");
    q.bindValue(":id", id);
    if (q.exec() && q.next()) {
        return Animal(q.value(0).toInt(), q.value(1).toString(), q.value(2).toString(), q.value(3).toString(),
                      q.value(4).toDate(), q.value(5).toString(), q.value(6).toString(), q.value(7).toString(),
                      q.value(8).toString(), healthFromString(q.value(9).toString()));
    }
    return Animal();
}

