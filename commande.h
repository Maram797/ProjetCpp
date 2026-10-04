#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>

class Commande
{
public:
    Commande();
    Commande(const QString &id, const QDate &dateLivraison, double montant,
             const QString &typeProduit, int quantite, const QString &etat);

    QString id() const { return m_id; }
    void setId(const QString &id) { m_id = id; }

    QDate dateLivraison() const { return m_dateLivraison; }
    void setDateLivraison(const QDate &d) { m_dateLivraison = d; }

    double montant() const { return m_montant; }
    void setMontant(double m) { m_montant = m; }

    QString typeProduit() const { return m_typeProduit; }
    void setTypeProduit(const QString &t) { m_typeProduit = t; }

    int quantite() const { return m_quantite; }
    void setQuantite(int q) { m_quantite = q; }

    QString etat() const { return m_etat; }
    void setEtat(const QString &e) { m_etat = e; }

private:
    QString m_id;
    QDate m_dateLivraison;
    double m_montant;
    QString m_typeProduit;
    int m_quantite;
    QString m_etat;
};

#endif // COMMANDE_H
