/********************************************************************************
** Form generated from reading UI file 'gestionrendezvous.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTIONRENDEZVOUS_H
#define UI_GESTIONRENDEZVOUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestionRendezvous
{
public:
    QWidget *centralwidget;
    QFrame *centralFrame;
    QFrame *sideBar;
    QLabel *logoLabel;
    QPushButton *btnAnimaux;
    QPushButton *btnClients;
    QPushButton *btnProduits;
    QPushButton *btnCaisse;
    QPushButton *btnConsultations;
    QFrame *mainContent;
    QPushButton *btnCabinet;
    QPushButton *btnNouveauPatient;
    QLabel *notifLabel;
    QLabel *avatarLabel;
    QLabel *posteLabel;
    QLabel *posteBadge;
    QLabel *salleLabel;
    QLabel *pageTitle;
    QLabel *pageSubtitle;
    QFrame *patientsFrame;
    QLabel *patientsTitle;
    QLabel *patientsCountBadge;
    QScrollArea *patientsScroll;
    QWidget *patientsContainer;
    QFrame *selectedPatientFrame;
    QLabel *avatarSelected;
    QLineEdit *patientName;
    QLabel *patientBreedAge;
    QLabel *ownerLabel;
    QLabel *dossierLabel;
    QLabel *genderLabel;
    QFrame *dateCard;
    QLabel *dateCaption;
    QLineEdit *champDate;
    QFrame *heureCard;
    QLabel *heureCaption;
    QLineEdit *champHeure;
    QFrame *nomCard;
    QLabel *nomCaption;
    QLineEdit *champNom;
    QFrame *telCard;
    QLabel *telCaption;
    QLineEdit *champTel;
    QFrame *motifCard;
    QLabel *motifCaption;
    QLineEdit *champMotif;
    QFrame *notesCard;
    QLabel *notesCaption;
    QLineEdit *champNotes;
    QLabel *motifTitle;
    QTextEdit *motifText;
    QLabel *diagnosticTitle;
    QTextEdit *diagnosticText;
    QLabel *actesTitle;
    QLabel *actesSubtitle;
    QPushButton *btnEnregistrer;
    QPushButton *btnExporterPreConsultation;
    QFrame *appointmentStatsFrame;
    QLabel *statsTitleLabel;
    QLabel *statTotalLabel;
    QLabel *statRealisesLabel;
    QLabel *statARealiserLabel;
    QPushButton *btnTrier;
    QLineEdit *searchBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GestionRendezvous)
    {
        if (GestionRendezvous->objectName().isEmpty())
            GestionRendezvous->setObjectName("GestionRendezvous");
        GestionRendezvous->resize(1300, 750);
        centralwidget = new QWidget(GestionRendezvous);
        centralwidget->setObjectName("centralwidget");
        centralFrame = new QFrame(centralwidget);
        centralFrame->setObjectName("centralFrame");
        centralFrame->setGeometry(QRect(0, -1, 1300, 750));
        centralFrame->setStyleSheet(QString::fromUtf8("QFrame#centralFrame {\n"
"	background-color : #FFF9F4\n"
"}"));
        centralFrame->setFrameShape(QFrame::Shape::StyledPanel);
        centralFrame->setFrameShadow(QFrame::Shadow::Raised);
        sideBar = new QFrame(centralFrame);
        sideBar->setObjectName("sideBar");
        sideBar->setGeometry(QRect(0, 0, 240, 750));
        sideBar->setStyleSheet(QString::fromUtf8("QFrame#sideBar { \n"
"	background-color : #FBF4EE ;\n"
"	border: 2px solid #E77C8D;\n"
"}"));
        sideBar->setFrameShape(QFrame::Shape::StyledPanel);
        sideBar->setFrameShadow(QFrame::Shadow::Raised);
        logoLabel = new QLabel(sideBar);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(20, 18, 200, 81));
        logoLabel->setStyleSheet(QString::fromUtf8("QLabel#logoLabel {\n"
"	color : #6B3F2E ;\n"
"	font-family : Arial ;\n"
"	background-color: transparent;\n"
"}"));
        logoLabel->setPixmap(QPixmap(QString::fromUtf8("../../../Downloads/pawche.jpeg")));
        logoLabel->setScaledContents(true);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnAnimaux = new QPushButton(sideBar);
        btnAnimaux->setObjectName("btnAnimaux");
        btnAnimaux->setGeometry(QRect(15, 105, 210, 45));
        btnAnimaux->setMinimumSize(QSize(210, 45));
        btnAnimaux->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnAnimaux->setStyleSheet(QString::fromUtf8("QPushButton#btnAnimaux {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-family: Arial;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnAnimaux:hover {\n"
"    background-color: #F9DEE4;\n"
"}\n"
"QPushButton#btnAnimaux:pressed {\n"
"    background-color: #E77C8D;\n"
"    color: white;\n"
"}"));
        btnClients = new QPushButton(sideBar);
        btnClients->setObjectName("btnClients");
        btnClients->setGeometry(QRect(10, 180, 210, 45));
        btnClients->setMinimumSize(QSize(210, 45));
        btnClients->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnClients->setStyleSheet(QString::fromUtf8("QPushButton#btnClients {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-family: Arial;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnClients:hover {\n"
"    background-color: #F9DEE4;\n"
"}\n"
"QPushButton#btnClients:pressed {\n"
"    background-color: #E77C8D;\n"
"    color: white;\n"
"}"));
        btnProduits = new QPushButton(sideBar);
        btnProduits->setObjectName("btnProduits");
        btnProduits->setGeometry(QRect(15, 325, 210, 45));
        btnProduits->setMinimumSize(QSize(210, 45));
        btnProduits->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnProduits->setStyleSheet(QString::fromUtf8("QPushButton#btnProduits {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-family: Arial;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnProduits:hover {\n"
"    background-color: #F9DEE4;\n"
"}\n"
"QPushButton#btnProduits:pressed {\n"
"    background-color: #E77C8D;\n"
"    color: white;\n"
"}"));
        btnCaisse = new QPushButton(sideBar);
        btnCaisse->setObjectName("btnCaisse");
        btnCaisse->setGeometry(QRect(15, 395, 210, 45));
        btnCaisse->setMinimumSize(QSize(210, 45));
        btnCaisse->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnCaisse->setStyleSheet(QString::fromUtf8("QPushButton#btnCaisse {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-family: Arial;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnCaisse:hover {\n"
"    background-color: #F9DEE4;\n"
"}\n"
"QPushButton#btnCaisse:pressed {\n"
"    background-color: #E77C8D;\n"
"    color: white;\n"
"}"));
        btnConsultations = new QPushButton(sideBar);
        btnConsultations->setObjectName("btnConsultations");
        btnConsultations->setGeometry(QRect(20, 250, 210, 45));
        btnConsultations->setMinimumSize(QSize(210, 45));
        btnConsultations->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnConsultations->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        btnConsultations->setStyleSheet(QString::fromUtf8("QPushButton#btnConsultations {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-family: Arial;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnConsultations:hover {\n"
"    background-color: #F9DEE4;\n"
"}\n"
"QPushButton#btnConsultations:pressed {\n"
"    background-color: #E77C8D;\n"
"    color: white;\n"
"}"));
        mainContent = new QFrame(centralFrame);
        mainContent->setObjectName("mainContent");
        mainContent->setGeometry(QRect(240, 0, 1060, 750));
        mainContent->setStyleSheet(QString::fromUtf8("QFrame#mainContent {\n"
"	background-color : #FBF4EE ;\n"
"}"));
        mainContent->setFrameShape(QFrame::Shape::StyledPanel);
        mainContent->setFrameShadow(QFrame::Shadow::Raised);
        btnCabinet = new QPushButton(mainContent);
        btnCabinet->setObjectName("btnCabinet");
        btnCabinet->setGeometry(QRect(600, 15, 150, 40));
        btnCabinet->setStyleSheet(QString::fromUtf8("QPushButton#btnCabinet {\n"
"	background-color: white;\n"
"	color: #6B3F2E;\n"
"	border: 1px solid #F3E6DC;\n"
"	border-radius: 8px;\n"
"	font-size: 12px;\n"
"	font-weight: bold;\n"
"}\n"
"QPushButton#btnCabinet:hover {\n"
"	background-color: #F9DEE4;\n"
"}"));
        btnNouveauPatient = new QPushButton(mainContent);
        btnNouveauPatient->setObjectName("btnNouveauPatient");
        btnNouveauPatient->setGeometry(QRect(760, 15, 170, 40));
        btnNouveauPatient->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnNouveauPatient->setStyleSheet(QString::fromUtf8("QPushButton#btnNouveauPatient {\n"
"	background-color: #6B3F2E;\n"
"	color: white;\n"
"	border: none;\n"
"	border-radius: 8px;\n"
"	font-size: 12px;\n"
"	font-weight: bold;\n"
"}\n"
"QPushButton#btnNouveauPatient:hover {\n"
"	background-color: #5A3225;\n"
"}"));
        notifLabel = new QLabel(mainContent);
        notifLabel->setObjectName("notifLabel");
        notifLabel->setGeometry(QRect(945, 18, 30, 30));
        notifLabel->setStyleSheet(QString::fromUtf8("QLabel#notifLabel {\n"
"	font-size : 16px ;\n"
"	background-color: transparent;\n"
"}"));
        notifLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        avatarLabel = new QLabel(mainContent);
        avatarLabel->setObjectName("avatarLabel");
        avatarLabel->setGeometry(QRect(985, 13, 40, 40));
        avatarLabel->setStyleSheet(QString::fromUtf8("QLabel#avatarLabel {\n"
"	background-color : #E77C8D ;\n"
"	color : white ;\n"
"	font-weight : bold ;\n"
"	border-radius : 20px ;\n"
"}"));
        avatarLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        posteLabel = new QLabel(mainContent);
        posteLabel->setObjectName("posteLabel");
        posteLabel->setGeometry(QRect(20, 68, 140, 18));
        posteLabel->setStyleSheet(QString::fromUtf8("QLabel#posteLabel {\n"
"	color : #A98268 ;\n"
"	font-size : 10px ;\n"
"	font-weight : bold ;\n"
"	background-color: transparent;\n"
"}"));
        posteBadge = new QLabel(mainContent);
        posteBadge->setObjectName("posteBadge");
        posteBadge->setGeometry(QRect(155, 64, 55, 22));
        posteBadge->setStyleSheet(QString::fromUtf8("QLabel#posteBadge {\n"
"	background-color : #F3E6DC ;\n"
"	color : #6B3F2E ;\n"
"	font-size : 10px ;\n"
"	font-weight : bold ;\n"
"	border-radius : 10px ;\n"
"}"));
        posteBadge->setAlignment(Qt::AlignmentFlag::AlignCenter);
        salleLabel = new QLabel(mainContent);
        salleLabel->setObjectName("salleLabel");
        salleLabel->setGeometry(QRect(900, 68, 140, 18));
        salleLabel->setStyleSheet(QString::fromUtf8("QLabel#salleLabel {\n"
"	color : #A98268 ;\n"
"	font-size : 11px ;\n"
"	background-color: transparent;\n"
"}"));
        salleLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        pageTitle = new QLabel(mainContent);
        pageTitle->setObjectName("pageTitle");
        pageTitle->setGeometry(QRect(20, 20, 350, 30));
        pageTitle->setStyleSheet(QString::fromUtf8("QLabel#pageTitle {\n"
"	color : #6B3F2E ;\n"
"	font-size : 20px ;\n"
"	font-weight : bold ;\n"
"	background-color: transparent;\n"
"}"));
        pageSubtitle = new QLabel(mainContent);
        pageSubtitle->setObjectName("pageSubtitle");
        pageSubtitle->setGeometry(QRect(20, 50, 350, 18));
        pageSubtitle->setStyleSheet(QString::fromUtf8("QLabel#pageSubtitle {\n"
"	color : #A98268 ;\n"
"	font-size : 11px ;\n"
"	background-color: transparent;\n"
"}"));
        patientsFrame = new QFrame(mainContent);
        patientsFrame->setObjectName("patientsFrame");
        patientsFrame->setGeometry(QRect(20, 160, 300, 470));
        patientsFrame->setStyleSheet(QString::fromUtf8("QFrame#patientsFrame {\n"
"    background-color: white;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 10px;\n"
"}"));
        patientsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        patientsFrame->setFrameShadow(QFrame::Shadow::Raised);
        patientsTitle = new QLabel(patientsFrame);
        patientsTitle->setObjectName("patientsTitle");
        patientsTitle->setGeometry(QRect(20, 30, 160, 22));
        patientsTitle->setStyleSheet(QString::fromUtf8("QLabel#patientsTitle {\n"
"    color: #6B3F2E;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        patientsCountBadge = new QLabel(patientsFrame);
        patientsCountBadge->setObjectName("patientsCountBadge");
        patientsCountBadge->setGeometry(QRect(210, 40, 75, 18));
        patientsCountBadge->setStyleSheet(QString::fromUtf8("QLabel#patientsCountBadge {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    background-color: transparent;\n"
"}"));
        patientsCountBadge->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        patientsScroll = new QScrollArea(patientsFrame);
        patientsScroll->setObjectName("patientsScroll");
        patientsScroll->setGeometry(QRect(10, 70, 290, 375));
        patientsScroll->setFrameShape(QFrame::Shape::NoFrame);
        patientsScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        patientsScroll->setWidgetResizable(true);
        patientsContainer = new QWidget();
        patientsContainer->setObjectName("patientsContainer");
        patientsContainer->setGeometry(QRect(0, 0, 290, 375));
        patientsScroll->setWidget(patientsContainer);
        selectedPatientFrame = new QFrame(mainContent);
        selectedPatientFrame->setObjectName("selectedPatientFrame");
        selectedPatientFrame->setGeometry(QRect(340, 160, 700, 470));
        selectedPatientFrame->setStyleSheet(QString::fromUtf8("QFrame#selectedPatientFrame {\n"
"    background-color: white;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 10px;\n"
"}"));
        selectedPatientFrame->setFrameShape(QFrame::Shape::StyledPanel);
        selectedPatientFrame->setFrameShadow(QFrame::Shadow::Raised);
        avatarSelected = new QLabel(selectedPatientFrame);
        avatarSelected->setObjectName("avatarSelected");
        avatarSelected->setGeometry(QRect(20, 20, 60, 60));
        avatarSelected->setStyleSheet(QString::fromUtf8("QLabel#avatarSelected {\n"
"    background-color: #F3E6DC;\n"
"    border-radius: 30px;\n"
"}"));
        avatarSelected->setAlignment(Qt::AlignmentFlag::AlignCenter);
        patientName = new QLineEdit(selectedPatientFrame);
        patientName->setObjectName("patientName");
        patientName->setGeometry(QRect(95, 20, 300, 30));
        patientName->setStyleSheet(QString::fromUtf8("QLabel#patientName {\n"
"    color: #6B3F2E;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        patientBreedAge = new QLabel(selectedPatientFrame);
        patientBreedAge->setObjectName("patientBreedAge");
        patientBreedAge->setGeometry(QRect(95, 50, 220, 20));
        patientBreedAge->setStyleSheet(QString::fromUtf8("QLabel#patientBreedAge {\n"
"    color: #A98268;\n"
"    font-size: 11px;\n"
"    background-color: transparent;\n"
"}"));
        ownerLabel = new QLabel(selectedPatientFrame);
        ownerLabel->setObjectName("ownerLabel");
        ownerLabel->setGeometry(QRect(95, 72, 300, 20));
        ownerLabel->setStyleSheet(QString::fromUtf8("QLabel#ownerLabel {\n"
"    color: #6B3F2E;\n"
"    font-size: 11px;\n"
"    background-color: transparent;\n"
"}"));
        dossierLabel = new QLabel(selectedPatientFrame);
        dossierLabel->setObjectName("dossierLabel");
        dossierLabel->setGeometry(QRect(530, 22, 150, 18));
        dossierLabel->setStyleSheet(QString::fromUtf8("QLabel#dossierLabel {\n"
"    color: #A98268;\n"
"    font-size: 11px;\n"
"    background-color: transparent;\n"
"}"));
        dossierLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        genderLabel = new QLabel(selectedPatientFrame);
        genderLabel->setObjectName("genderLabel");
        genderLabel->setGeometry(QRect(530, 42, 150, 18));
        genderLabel->setStyleSheet(QString::fromUtf8("QLabel#genderLabel {\n"
"    color: #E77C8D;\n"
"    font-size: 11px;\n"
"    background-color: transparent;\n"
"}"));
        genderLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dateCard = new QFrame(selectedPatientFrame);
        dateCard->setObjectName("dateCard");
        dateCard->setGeometry(QRect(20, 100, 150, 56));
        dateCard->setStyleSheet(QString::fromUtf8("QFrame#dateCard {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"}"));
        dateCard->setFrameShape(QFrame::Shape::StyledPanel);
        dateCard->setFrameShadow(QFrame::Shadow::Raised);
        dateCaption = new QLabel(dateCard);
        dateCaption->setObjectName("dateCaption");
        dateCaption->setGeometry(QRect(12, 6, 126, 14));
        dateCaption->setStyleSheet(QString::fromUtf8("QLabel#dateCaption {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        champDate = new QLineEdit(dateCard);
        champDate->setObjectName("champDate");
        champDate->setGeometry(QRect(12, 23, 126, 26));
        champDate->setStyleSheet(QString::fromUtf8("QLineEdit#champDate {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-bottom: 1px solid transparent;\n"
"    padding: 0px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit#champDate:focus {\n"
"    border-bottom: 1px solid #E77C8D;\n"
"}"));
        heureCard = new QFrame(selectedPatientFrame);
        heureCard->setObjectName("heureCard");
        heureCard->setGeometry(QRect(180, 100, 100, 56));
        heureCard->setStyleSheet(QString::fromUtf8("QFrame#heureCard {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"}"));
        heureCard->setFrameShape(QFrame::Shape::StyledPanel);
        heureCard->setFrameShadow(QFrame::Shadow::Raised);
        heureCaption = new QLabel(heureCard);
        heureCaption->setObjectName("heureCaption");
        heureCaption->setGeometry(QRect(12, 6, 76, 14));
        heureCaption->setStyleSheet(QString::fromUtf8("QLabel#heureCaption {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        champHeure = new QLineEdit(heureCard);
        champHeure->setObjectName("champHeure");
        champHeure->setGeometry(QRect(12, 23, 76, 26));
        champHeure->setStyleSheet(QString::fromUtf8("QLineEdit#champHeure {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-bottom: 1px solid transparent;\n"
"    padding: 0px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit#champHeure:focus {\n"
"    border-bottom: 1px solid #E77C8D;\n"
"}"));
        nomCard = new QFrame(selectedPatientFrame);
        nomCard->setObjectName("nomCard");
        nomCard->setGeometry(QRect(290, 100, 190, 56));
        nomCard->setStyleSheet(QString::fromUtf8("QFrame#nomCard {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"}"));
        nomCard->setFrameShape(QFrame::Shape::StyledPanel);
        nomCard->setFrameShadow(QFrame::Shadow::Raised);
        nomCaption = new QLabel(nomCard);
        nomCaption->setObjectName("nomCaption");
        nomCaption->setGeometry(QRect(12, 6, 166, 14));
        nomCaption->setStyleSheet(QString::fromUtf8("QLabel#nomCaption {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        champNom = new QLineEdit(nomCard);
        champNom->setObjectName("champNom");
        champNom->setGeometry(QRect(12, 23, 166, 26));
        champNom->setStyleSheet(QString::fromUtf8("QLineEdit#champNom {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-bottom: 1px solid transparent;\n"
"    padding: 0px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit#champNom:focus {\n"
"    border-bottom: 1px solid #E77C8D;\n"
"}"));
        telCard = new QFrame(selectedPatientFrame);
        telCard->setObjectName("telCard");
        telCard->setGeometry(QRect(490, 100, 190, 56));
        telCard->setStyleSheet(QString::fromUtf8("QFrame#telCard {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"}"));
        telCard->setFrameShape(QFrame::Shape::StyledPanel);
        telCard->setFrameShadow(QFrame::Shadow::Raised);
        telCaption = new QLabel(telCard);
        telCaption->setObjectName("telCaption");
        telCaption->setGeometry(QRect(12, 6, 166, 14));
        telCaption->setStyleSheet(QString::fromUtf8("QLabel#telCaption {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        champTel = new QLineEdit(telCard);
        champTel->setObjectName("champTel");
        champTel->setGeometry(QRect(12, 23, 166, 26));
        champTel->setStyleSheet(QString::fromUtf8("QLineEdit#champTel {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-bottom: 1px solid transparent;\n"
"    padding: 0px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit#champTel:focus {\n"
"    border-bottom: 1px solid #E77C8D;\n"
"}"));
        motifCard = new QFrame(selectedPatientFrame);
        motifCard->setObjectName("motifCard");
        motifCard->setGeometry(QRect(20, 164, 320, 56));
        motifCard->setStyleSheet(QString::fromUtf8("QFrame#motifCard {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"}"));
        motifCard->setFrameShape(QFrame::Shape::StyledPanel);
        motifCard->setFrameShadow(QFrame::Shadow::Raised);
        motifCaption = new QLabel(motifCard);
        motifCaption->setObjectName("motifCaption");
        motifCaption->setGeometry(QRect(12, 6, 296, 14));
        motifCaption->setStyleSheet(QString::fromUtf8("QLabel#motifCaption {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        champMotif = new QLineEdit(motifCard);
        champMotif->setObjectName("champMotif");
        champMotif->setGeometry(QRect(12, 23, 296, 26));
        champMotif->setStyleSheet(QString::fromUtf8("QLineEdit#champMotif {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-bottom: 1px solid transparent;\n"
"    padding: 0px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit#champMotif:focus {\n"
"    border-bottom: 1px solid #E77C8D;\n"
"}"));
        notesCard = new QFrame(selectedPatientFrame);
        notesCard->setObjectName("notesCard");
        notesCard->setGeometry(QRect(350, 164, 330, 56));
        notesCard->setStyleSheet(QString::fromUtf8("QFrame#notesCard {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"}"));
        notesCard->setFrameShape(QFrame::Shape::StyledPanel);
        notesCard->setFrameShadow(QFrame::Shadow::Raised);
        notesCaption = new QLabel(notesCard);
        notesCaption->setObjectName("notesCaption");
        notesCaption->setGeometry(QRect(12, 6, 306, 14));
        notesCaption->setStyleSheet(QString::fromUtf8("QLabel#notesCaption {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        champNotes = new QLineEdit(notesCard);
        champNotes->setObjectName("champNotes");
        champNotes->setGeometry(QRect(12, 23, 306, 26));
        champNotes->setStyleSheet(QString::fromUtf8("QLineEdit#champNotes {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    border-bottom: 1px solid transparent;\n"
"    padding: 0px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QLineEdit#champNotes:focus {\n"
"    border-bottom: 1px solid #E77C8D;\n"
"}"));
        motifTitle = new QLabel(selectedPatientFrame);
        motifTitle->setObjectName("motifTitle");
        motifTitle->setGeometry(QRect(20, 235, 250, 18));
        motifTitle->setStyleSheet(QString::fromUtf8("QLabel#motifTitle {\n"
"    color: #6B3F2E;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        motifText = new QTextEdit(selectedPatientFrame);
        motifText->setObjectName("motifText");
        motifText->setGeometry(QRect(20, 258, 660, 55));
        motifText->setStyleSheet(QString::fromUtf8("QTextEdit#motifText {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"    color: #6B3F2E;\n"
"    font-size: 11px;\n"
"    padding: 6px;\n"
"}"));
        diagnosticTitle = new QLabel(selectedPatientFrame);
        diagnosticTitle->setObjectName("diagnosticTitle");
        diagnosticTitle->setGeometry(QRect(20, 325, 250, 18));
        diagnosticTitle->setStyleSheet(QString::fromUtf8("QLabel#diagnosticTitle {\n"
"    color: #6B3F2E;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        diagnosticText = new QTextEdit(selectedPatientFrame);
        diagnosticText->setObjectName("diagnosticText");
        diagnosticText->setGeometry(QRect(20, 348, 660, 45));
        diagnosticText->setStyleSheet(QString::fromUtf8("QTextEdit#diagnosticText {\n"
"    background-color: #FDFBF9;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"    color: #6B3F2E;\n"
"    font-size: 11px;\n"
"    padding: 6px;\n"
"}"));
        actesTitle = new QLabel(selectedPatientFrame);
        actesTitle->setObjectName("actesTitle");
        actesTitle->setGeometry(QRect(20, 408, 250, 18));
        actesTitle->setStyleSheet(QString::fromUtf8("QLabel#actesTitle {\n"
"    color: #6B3F2E;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        actesSubtitle = new QLabel(selectedPatientFrame);
        actesSubtitle->setObjectName("actesSubtitle");
        actesSubtitle->setGeometry(QRect(20, 430, 400, 16));
        actesSubtitle->setStyleSheet(QString::fromUtf8("QLabel#actesSubtitle {\n"
"    color: #A98268;\n"
"    font-size: 10px;\n"
"    background-color: transparent;\n"
"}"));
        btnEnregistrer = new QPushButton(selectedPatientFrame);
        btnEnregistrer->setObjectName("btnEnregistrer");
        btnEnregistrer->setEnabled(false);
        btnEnregistrer->setGeometry(QRect(540, 420, 140, 28));
        btnEnregistrer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnEnregistrer->setStyleSheet(QString::fromUtf8("QPushButton#btnEnregistrer {\n"
"    background-color: #6B3F2E;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnEnregistrer:hover {\n"
"    background-color: #5A3225;\n"
"}\n"
"QPushButton#btnEnregistrer:disabled {\n"
"    background-color: #A98268;\n"
"}"));
        btnExporterPreConsultation = new QPushButton(selectedPatientFrame);
        btnExporterPreConsultation->setObjectName("btnExporterPreConsultation");
        btnExporterPreConsultation->setGeometry(QRect(320, 420, 205, 28));
        btnExporterPreConsultation->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnExporterPreConsultation->setStyleSheet(QString::fromUtf8("QPushButton#btnExporterPreConsultation {\n"
"    background-color: white;\n"
"    color: #6B3F2E;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 8px;\n"
"    font-size: 10px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnExporterPreConsultation:hover {\n"
"    background-color: #F9DEE4;\n"
"}"));
        appointmentStatsFrame = new QFrame(mainContent);
        appointmentStatsFrame->setObjectName("appointmentStatsFrame");
        appointmentStatsFrame->setGeometry(QRect(20, 610, 1020, 130));
        appointmentStatsFrame->setStyleSheet(QString::fromUtf8("QFrame#appointmentStatsFrame {\n"
"    background-color: white;\n"
"    border: 1px solid #F3E6DC;\n"
"    border-radius: 10px;\n"
"}"));
        appointmentStatsFrame->setFrameShape(QFrame::Shape::StyledPanel);
        appointmentStatsFrame->setFrameShadow(QFrame::Shadow::Raised);
        statsTitleLabel = new QLabel(appointmentStatsFrame);
        statsTitleLabel->setObjectName("statsTitleLabel");
        statsTitleLabel->setGeometry(QRect(20, 10, 240, 22));
        statsTitleLabel->setStyleSheet(QString::fromUtf8("QLabel#statsTitleLabel {\n"
"    color: #6B3F2E;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        statTotalLabel = new QLabel(appointmentStatsFrame);
        statTotalLabel->setObjectName("statTotalLabel");
        statTotalLabel->setGeometry(QRect(285, 10, 220, 22));
        statTotalLabel->setStyleSheet(QString::fromUtf8("QLabel#statTotalLabel {\n"
"    color: #6B3F2E;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        statRealisesLabel = new QLabel(appointmentStatsFrame);
        statRealisesLabel->setObjectName("statRealisesLabel");
        statRealisesLabel->setGeometry(QRect(530, 10, 180, 22));
        statRealisesLabel->setStyleSheet(QString::fromUtf8("QLabel#statRealisesLabel {\n"
"    color: #2E7D46;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        statARealiserLabel = new QLabel(appointmentStatsFrame);
        statARealiserLabel->setObjectName("statARealiserLabel");
        statARealiserLabel->setGeometry(QRect(735, 10, 220, 22));
        statARealiserLabel->setStyleSheet(QString::fromUtf8("QLabel#statARealiserLabel {\n"
"    color: #A98268;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    background-color: transparent;\n"
"}"));
        btnTrier = new QPushButton(mainContent);
        btnTrier->setObjectName("btnTrier");
        btnTrier->setGeometry(QRect(450, 110, 130, 40));
        btnTrier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnTrier->setStyleSheet(QString::fromUtf8("QPushButton#btnTrier {\n"
"	background-color: white;\n"
"	color: #6B3F2E;\n"
"	border: 1px solid #F3E6DC;\n"
"	border-radius: 8px;\n"
"	font-size: 12px;\n"
"	font-weight: bold;\n"
"	text-align: left;\n"
"	padding-left: 12px;\n"
"}\n"
"QPushButton#btnTrier:hover {\n"
"	background-color: #F9DEE4;\n"
"}\n"
"QPushButton#btnTrier::menu-indicator {\n"
"	right: 10px;\n"
"}"));
        searchBar = new QLineEdit(mainContent);
        searchBar->setObjectName("searchBar");
        searchBar->setGeometry(QRect(20, 110, 420, 40));
        searchBar->setMinimumSize(QSize(0, 40));
        searchBar->setStyleSheet(QString::fromUtf8("QLineEdit#searchBar {\n"
"	background-color : white ;\n"
"	color : #6B3F2E ;\n"
"	border : 1px solid #F3E6DC ;\n"
"	border-radius : 20px ;\n"
"	padding-left : 15px ;\n"
"	font-size : 12px ; \n"
"}"));
        GestionRendezvous->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GestionRendezvous);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1300, 25));
        GestionRendezvous->setMenuBar(menubar);
        statusbar = new QStatusBar(GestionRendezvous);
        statusbar->setObjectName("statusbar");
        GestionRendezvous->setStatusBar(statusbar);

        retranslateUi(GestionRendezvous);

        QMetaObject::connectSlotsByName(GestionRendezvous);
    } // setupUi

    void retranslateUi(QMainWindow *GestionRendezvous)
    {
        GestionRendezvous->setWindowTitle(QCoreApplication::translate("GestionRendezvous", "gestion veterinaire", nullptr));
        logoLabel->setText(QString());
        btnAnimaux->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\220\276  Gestion des Animaux", nullptr));
        btnClients->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\221\245  Propri\303\251taires & Clients", nullptr));
        btnProduits->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\223\246  Produits & Stock", nullptr));
        btnCaisse->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\222\260  Facturation & Caisse", nullptr));
        btnConsultations->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\251\272 Gestion des rendez-vous", nullptr));
        btnCabinet->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\227\202  Cabinet Principal", nullptr));
        btnNouveauPatient->setText(QCoreApplication::translate("GestionRendezvous", "+  Nouveau Patient", nullptr));
        notifLabel->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\224\224", nullptr));
        avatarLabel->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\221\244", nullptr));
        posteLabel->setText(QCoreApplication::translate("GestionRendezvous", "POSTE VETERINAIRE", nullptr));
        posteBadge->setText(QCoreApplication::translate("GestionRendezvous", "POST-01", nullptr));
        salleLabel->setText(QCoreApplication::translate("GestionRendezvous", "Salle d'examen \342\200\224", nullptr));
        pageTitle->setText(QCoreApplication::translate("GestionRendezvous", "Gestion des rendez-vous", nullptr));
        pageSubtitle->setText(QCoreApplication::translate("GestionRendezvous", "Session active \342\200\242 \342\200\224", nullptr));
        patientsTitle->setText(QCoreApplication::translate("GestionRendezvous", "Patients du jour", nullptr));
        patientsCountBadge->setText(QCoreApplication::translate("GestionRendezvous", "\342\200\224 en attente", nullptr));
        avatarSelected->setText(QCoreApplication::translate("GestionRendezvous", "\360\237\220\276", nullptr));
        patientName->setText(QCoreApplication::translate("GestionRendezvous", "Patient name", nullptr));
        patientName->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Nom de l'animal", nullptr));
        patientBreedAge->setText(QCoreApplication::translate("GestionRendezvous", "\342\200\224 \342\200\242 \342\200\224", nullptr));
        ownerLabel->setText(QCoreApplication::translate("GestionRendezvous", "Propri\303\251taire : \342\200\224", nullptr));
        dossierLabel->setText(QCoreApplication::translate("GestionRendezvous", "Dossier #------", nullptr));
        genderLabel->setText(QCoreApplication::translate("GestionRendezvous", "\342\200\224", nullptr));
        dateCaption->setText(QCoreApplication::translate("GestionRendezvous", "DATE", nullptr));
        champDate->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "jj/mm/aaaa", nullptr));
        heureCaption->setText(QCoreApplication::translate("GestionRendezvous", "HEURE", nullptr));
        champHeure->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "hh:mm", nullptr));
        nomCaption->setText(QCoreApplication::translate("GestionRendezvous", "NOM DE L'ANIMAL", nullptr));
        champNom->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Nom de l'animal", nullptr));
        telCaption->setText(QCoreApplication::translate("GestionRendezvous", "T\303\211L\303\211PHONE", nullptr));
        champTel->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "T\303\251l\303\251phone du propri\303\251taire", nullptr));
        motifCaption->setText(QCoreApplication::translate("GestionRendezvous", "MOTIF", nullptr));
        champMotif->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Motif de la visite", nullptr));
        notesCaption->setText(QCoreApplication::translate("GestionRendezvous", "NOTES", nullptr));
        champNotes->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Notes", nullptr));
        motifTitle->setText(QCoreApplication::translate("GestionRendezvous", "Constatations", nullptr));
        motifText->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Constatations de l'examen clinique\342\200\246", nullptr));
        diagnosticTitle->setText(QCoreApplication::translate("GestionRendezvous", "Diagnostic retenu", nullptr));
        diagnosticText->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Diagnostic retenu\342\200\246", nullptr));
        actesTitle->setText(QCoreApplication::translate("GestionRendezvous", "Actes & Prescriptions", nullptr));
        actesSubtitle->setText(QCoreApplication::translate("GestionRendezvous", "Prestations et traitements appliqu\303\251s lors de la s\303\251ance", nullptr));
        btnEnregistrer->setText(QCoreApplication::translate("GestionRendezvous", "Enregistr\303\251", nullptr));
        btnExporterPreConsultation->setText(QCoreApplication::translate("GestionRendezvous", "Exporter la pr\303\251-consultation PDF", nullptr));
        statsTitleLabel->setText(QCoreApplication::translate("GestionRendezvous", "Statistiques des rendez-vous", nullptr));
        statTotalLabel->setText(QCoreApplication::translate("GestionRendezvous", "Total des rendez-vous : 0", nullptr));
        statRealisesLabel->setText(QCoreApplication::translate("GestionRendezvous", "R\303\251alis\303\251s : 0", nullptr));
        statARealiserLabel->setText(QCoreApplication::translate("GestionRendezvous", "\303\200 r\303\251aliser : 0", nullptr));
        btnTrier->setText(QCoreApplication::translate("GestionRendezvous", "\342\207\205  Trier", nullptr));
        searchBar->setPlaceholderText(QCoreApplication::translate("GestionRendezvous", "Rechercher les rendez-vous selon le nom ...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestionRendezvous: public Ui_GestionRendezvous {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTIONRENDEZVOUS_H
