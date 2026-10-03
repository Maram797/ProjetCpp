#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Un patient (une fiche / un dossier). Chaque patient a un numero de dossier
// unique, attribue a la creation et jamais reutilise.
struct Patient
{
    int     id = 0;            // numero d'ordre de creation (1, 2, 3...)
    QString dossier;           // numero de dossier unique, ex. "DOS-2026-0007"
    QString nom;               // nom de l'animal
    QDate   date;
    QTime   heure;
    QString motif;
    QString telephone;
    QString notes;
    QString constatations;
    QString diagnostic;
    QString statut     = "En attente";
    QString statutType = "neutre";   // succes | alerte | neutre
    bool    rendezVousRealise = false;
};

// Charte graphique de l'application : genere les feuilles de style Qt (QSS)
// a partir d'une seule palette de couleurs. Utilisee par MainWindow.
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Change le badge de statut d'un patient de la liste (numero = id du patient,
    // 1 pour le premier patient cree, etc.).
    // type : "succes" (vert), "alerte" (rouge) ou "neutre"
    void setStatutPatient(int numero, const QString &texte, const QString &type);

private slots:
    void nouveauPatient();                 // bouton "+ Nouveau Patient"
    void selectionnerPatient(int id);      // clic sur un patient de la liste
    void appliquerTri(int critere);        // menu du bouton "Trier"
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
    void configurerChamps();  // champs editables + connexions
    void configurerTri();     // menu du bouton "Trier"

    int      ajouterPatient(const QString &nom, const QDate &date, const QTime &heure);
    QString  genererDossier();
    Patient *trouver(int id);
    Patient *patientCourant();

    void reconstruireListe();             // recree les lignes dans l'ordre de tri
    void majLigne(int id);                // met a jour le texte d'une ligne
    void majCompteur();
    void majStatistiques();
    void afficherPatient(const Patient &p);
    void appliquerModeEdition(bool actif);

    Ui::MainWindow *ui;
    charte m_charte;          // palette unique de l'application

    QVector<Patient> m_patients;      // dans l'ordre de creation
    int  m_dernierId     = 0;
    int  m_courant       = -1;        // id du patient affiche
    int  m_critereTri    = NumeroDossier;
    bool m_chargement    = false;     // true pendant le remplissage des champs
    bool m_modeEdition   = false;

    QVBoxLayout  *m_listeLayout = nullptr;
    QButtonGroup *m_groupe      = nullptr;
    AppointmentChart *m_graphiqueRendezVous = nullptr;
};

#endif // MAINWINDOW_H