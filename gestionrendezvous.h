#ifndef GESTIONRENDEZVOUS_H
#define GESTIONRENDEZVOUS_H

#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <string>


class QButtonGroup;
class QVBoxLayout;
class QPushButton;
class AppointmentChart;

QT_BEGIN_NAMESPACE
namespace Ui { class GestionRendezvous; }
QT_END_NAMESPACE


struct Patient
{
    int     id = 0;            
    QString dossier;           
    QString nom;               
    QDate   date;
    QTime   heure;
    QString motif;
    QString telephone;
    QString notes;
    QString constatations;
    QString diagnostic;
    QString statut     = "En attente";
    QString statutType = "neutre";   
    bool    rendezVousRealise = false;

    // Cle du rendez-vous telle qu'elle est enregistree dans Oracle
    // (la table n'a pas de colonne ID : on retrouve la ligne avec ces 3 valeurs)
    bool    enBase   = false;
    QString cleHeure;   // 'YYYY-MM-DD HH24:MI:SS.FF6'
    QString cleDate;    // 'YYYY-MM-DD'
    QString cleTel;     // chiffres uniquement
};


class charte
{
private:
    // Couleurs
    std::string fondPrincipal;
    std::string fondSidebar;
    std::string texteBrun;
    std::string texteSecondaire;
    std::string bordure;
    std::string survol;
    std::string accent;
    // Typographie et formes
    std::string police;
    int tailleTitre;
    int tailleTexte;
    int taillePetit;
    int rayon;
    std::string couleurStatut(std::string type, bool fond) const;
    std::string enTexte(int n) const;

public:
    charte();
    charte(std::string, std::string, std::string);
    charte(std::string, std::string, std::string, std::string, std::string,
           std::string, std::string, std::string, int, int, int, int);

    // zone : "principal" ou "sidebar"
    std::string styleFond(std::string nom, std::string zone) const;
    // barre laterale : fond de la sidebar + cadre exterieur bien visible
    std::string styleSidebar(std::string nom) const;
    std::string styleCadre(std::string nom, std::string couleurFond) const;
    std::string styleCarte(std::string nom) const;
    std::string styleBoutonMenu(std::string nom) const;
    std::string styleBoutonPrincipal(std::string nom) const;
    std::string styleBoutonSecondaire(std::string nom, bool aligneGauche = false) const;
    std::string styleBoutonPatient(std::string nom) const;
    // type : titre, sous-titre, section, rubrique, nom, valeur, texte,
    //        petit, etiquette, accent (sinon texte normal)
    std::string styleLabel(std::string nom, std::string type) const;
    // type : succes, alerte, neutre
    std::string styleStatut(std::string nom, std::string type) const;
    std::string styleAvatar(std::string nom, int diametre, bool accentue = false) const;
    std::string styleChampTexte(std::string nom) const;
    // champ de saisie "discret" (sans cadre, souligne a la saisie) pour les
    // fiches : type = "nom" (grand titre) ou "valeur" (champ des cartes)
    std::string styleChampDiscret(std::string nom, std::string type) const;
    std::string styleMenu(std::string nom) const;
    std::string styleScrollListe(std::string nom) const;
    std::string styleZoneTexte(std::string nom) const;
    void afficher() const;
};

class GestionRendezvous : public QMainWindow
{
    Q_OBJECT

public:
    GestionRendezvous(QWidget *parent = nullptr);
    ~GestionRendezvous();


    void setStatutPatient(int numero, const QString &texte, const QString &type);

private slots:
    void nouveauPatient();                
    void selectionnerPatient(int id);      
    void appliquerTri(int critere);        
    void modifierPatient(int id);
    void supprimerPatient(int id);
    void enregistrerPatient();
    void exporterPreConsultationPdf();

private:
    enum Tri { HeureCroissante, HeureDecroissante, NomAZ, NomZA,
               MotifAZ, StatutUrgentsDabord, NumeroDossier };

    void appliquer(const QString &nom, const std::string &style);
    void appliquerCharte();   // applique la charte graphique a tous les widgets
    void chargerLogo();
    void configurerChamps();  
    void configurerTri();     

    int      ajouterPatient(const QString &nom, const QDate &date, const QTime &heure);
    QString  genererDossier();
    Patient *trouver(int id);
    Patient *patientCourant();

    void reconstruireListe();          
    void majLigne(int id);                
    void majCompteur();
    void majStatistiques();
    void afficherPatient(const Patient &p);
    void appliquerModeEdition(bool actif);

    // --- Base de donnees Oracle (table GESTIONRENDEZVOUS) ---
    void chargerDepuisBase();                // lit les rendez-vous au demarrage
    bool sauvegarderEnBase(Patient &p);      // INSERT ou UPDATE
    bool supprimerEnBase(const Patient &p);  // DELETE

    Ui::GestionRendezvous *ui;
    charte m_charte;          

    QVector<Patient> m_patients;      
    int  m_dernierId     = 0;
    int  m_courant       = -1;        
    int  m_critereTri    = NumeroDossier;
    bool m_chargement    = false;     
    bool m_modeEdition   = false;

    QVBoxLayout  *m_listeLayout = nullptr;
    QButtonGroup *m_groupe      = nullptr;
    AppointmentChart *m_graphiqueRendezVous = nullptr;
};

#endif // GESTIONRENDEZVOUS_H