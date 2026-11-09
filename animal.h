#include <QColor>
#include <QDate>
#include <QString>

class QSqlQueryModel;

QString ageText(int years);

class Animal {
public:
    enum class Health { Sain, EnSoin, Urgent };

    Animal();
    Animal(const QString &nom, const QString &espece, const QString &race,
           const QDate &dateNaissance, const QString &puce, const QString &vaccinal,
           const QString &proprietaire, const QString &telephone, Health sante);

    static QString healthText(Health h);
    static QColor healthColor(Health h);

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel *trierParDateNaissance(bool ascendant = true);

    static bool ensureTable();

private:
    QString m_nom;
    QString m_espece = QStringLiteral("Chien");
    QString m_race;
    QDate   m_dateNaissance;
    QString m_puce;
    QString m_vaccinal = QStringLiteral("À jour");
    QString m_proprietaire;
    QString m_telephone;
    Health m_sante = Health::Sain;
};
