#ifndef GESTIONRENDEZVOUS_H
#define GESTIONRENDEZVOUS_H

#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>


class QButtonGroup;
class QVBoxLayout;
class QPushButton;
class QWidget;
class AppointmentChart;

QT_BEGIN_NAMESPACE
namespace Ui { class GestionRendezvous; }
QT_END_NAMESPACE

struct Patient
{
    int id = 0;
    qint64 idAnimal = 0;
    QString dossier;
    QString nom;
    QString proprietaire;
    QDate date;
    QTime heure;
    QString motif;
    QString telephone;
    QString notes;
    QString constatations;
    QString diagnostic;
    QString statut = "En attente";
    QString statutType = "neutre";
    bool rendezVousRealise = false;

    bool enBase = false;
    QString cleTelephone;
};

class PatientModel
{
public:
    bool charger(QVector<Patient> &patients, QString &erreur);
    bool sauvegarder(Patient &patient, QString &erreur);
    bool supprimer(const Patient &patient, QString &erreur);
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
    void modifierPatient(int id);
    void supprimerPatient(int id);
    void enregistrerPatient();
    void exporterPreConsultationPdf();

private:
    enum Tri { HeureCroissante, HeureDecroissante, MotifAZ, MotifZA };

    void chargerLogo();
    void configurerChamps();  
    void configurerTri();     

    int      ajouterPatient(const QString &nom, const QDate &date, const QTime &heure);
    Patient *trouver(int id);
    Patient *patientCourant();

    void reconstruireListe();          
    void majLigne(int id);                
    void majCompteur();
    void afficherPatient(const Patient &p);
    void appliquerModeEdition(bool actif);

    
    void chargerDepuisBase();

    Ui::GestionRendezvous *ui;

    PatientModel m_patientModel;
    QVector<Patient> m_patients;      
    QString m_rechercheMotif;
    int  m_dernierId     = 0;
    int  m_courant       = -1;        
    int  m_critereTri    = HeureCroissante;
    bool m_modeEdition   = false;

    QVBoxLayout  *m_listeLayout = nullptr;
    QWidget *m_patientsContainer = nullptr;
    QButtonGroup *m_groupe      = nullptr;
    QVector<QPushButton *> m_actions;
    AppointmentChart *m_graphiqueRendezVous = nullptr;
};

#endif 