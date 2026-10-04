#include "commande.h"

Commande::Commande()
    : m_montant(0.0), m_quantite(0)
{
}

Commande::Commande(const QString &id, const QDate &dateLivraison, double montant,
                   const QString &typeProduit, int quantite, const QString &etat)
    : m_id(id),
      m_dateLivraison(dateLivraison),
      m_montant(montant),
      m_typeProduit(typeProduit),
      m_quantite(quantite),
      m_etat(etat)
{
}
