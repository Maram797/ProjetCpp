/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "curvestatswidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainHLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *sidebarVLayout;
    QLabel *labelLogo;
    QSpacerItem *spacerLogo;
    QPushButton *btnNavAnimaux;
    QPushButton *btnNavProprietaires;
    QPushButton *btnNavSoins;
    QPushButton *btnNavCommandes;
    QPushButton *btnNavProduits;
    QPushButton *btnNavPaiements;
    QSpacerItem *sidebarSpacer;
    QPushButton *btnNavParametre;
    QPushButton *btnNavAide;
    QVBoxLayout *centerVLayout;
    QLabel *lblTitle;
    QLabel *lblSubtitle;
    QHBoxLayout *searchHLayout;
    QLineEdit *inputSearch;
    QComboBox *comboFilterType;
    QHBoxLayout *toolsHLayout;
    QLabel *lblListTitle;
    QSpacerItem *toolsSpacer;
    QPushButton *btnTrierPrix;
    QPushButton *btnTrierDate;
    QPushButton *btnExportPdf;
    QTableWidget *tableCommandes;
    QHBoxLayout *bottomHLayout;
    QFrame *statsFrame;
    QVBoxLayout *statsVLayout;
    QLabel *lblStatsTitle;
    CurveStatsWidget *widgetCurve;
    QFrame *alertFrame;
    QVBoxLayout *alertVLayout;
    QLabel *lblAlertHeading;
    QLabel *lblAlertBadge;
    QLabel *lblAlertDesc;
    QLabel *lblTotalMontant;
    QFrame *formFrame;
    QVBoxLayout *formVLayout;
    QLabel *lblFormBanner;
    QLabel *lblFormCircle;
    QHBoxLayout *rowIdLayout;
    QLabel *tagId;
    QLineEdit *txtId;
    QHBoxLayout *rowDateLayout;
    QLabel *tagDate;
    QDateEdit *dateLivraison;
    QHBoxLayout *rowMontantLayout;
    QLabel *tagMontant;
    QDoubleSpinBox *spinMontant;
    QHBoxLayout *rowTypeLayout;
    QLabel *tagType;
    QComboBox *comboType;
    QHBoxLayout *rowQteLayout;
    QLabel *tagQte;
    QSpinBox *spinQuantite;
    QHBoxLayout *rowEtatLayout;
    QLabel *tagEtat;
    QComboBox *comboEtat;
    QSpacerItem *formSpacer;
    QGridLayout *buttonsGrid;
    QPushButton *btnAjouter;
    QPushButton *btnModifier;
    QPushButton *btnSupprimer;
    QPushButton *btnVider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1240, 780);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"        background-color: #FAF5F0;\n"
"    }\n"
"    QWidget#centralwidget {\n"
"        background-color: #FAF5F0;\n"
"    }\n"
"    QFrame#sidebarFrame {\n"
"        background-color: #FFFDF9;\n"
"        border: 1px solid #EFE4DC;\n"
"        border-radius: 16px;\n"
"    }\n"
"    QPushButton.navButton {\n"
"        background-color: transparent;\n"
"        border: 1px solid #D9C3B5;\n"
"        border-radius: 8px;\n"
"        padding: 9px 12px;\n"
"        text-align: center;\n"
"        color: #5C3826;\n"
"        font-family: \"Segoe UI\", sans-serif;\n"
"        font-size: 11px;\n"
"        font-weight: 600;\n"
"    }\n"
"    QPushButton.navButton:hover {\n"
"        background-color: #F8EEE6;\n"
"        border-color: #633927;\n"
"    }\n"
"    QPushButton.navButtonActive {\n"
"        background-color: #633927;\n"
"        border: 1px solid #633927;\n"
"        border-radius: 8px;\n"
"        padding: 9px 12px;\n"
"        text-align: center;\n"
"        color: #FFFFFF;\n"
""
                        "        font-family: \"Segoe UI\", sans-serif;\n"
"        font-size: 11px;\n"
"        font-weight: bold;\n"
"    }\n"
"    QFrame.cardFrame {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #EFE6DF;\n"
"        border-radius: 14px;\n"
"    }\n"
"    QLineEdit, QDateEdit, QDoubleSpinBox, QSpinBox, QComboBox {\n"
"        background-color: #FFFFFF;\n"
"        border: 1.5px solid #D9C3B5;\n"
"        border-radius: 8px;\n"
"        padding: 6px 10px;\n"
"        color: #3D2619;\n"
"        font-family: \"Segoe UI\", sans-serif;\n"
"        font-size: 11px;\n"
"    }\n"
"    QLineEdit:focus, QDateEdit:focus, QDoubleSpinBox:focus, QSpinBox:focus, QComboBox:focus {\n"
"        border: 1.5px solid #633927;\n"
"        background-color: #FFFDF9;\n"
"    }\n"
"    QTableWidget {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #EFE6DF;\n"
"        border-radius: 12px;\n"
"        gridline-color: #F5EEE9;\n"
"        color: #3D2619;\n"
"        font-family: \"Segoe UI\", sans-"
                        "serif;\n"
"        font-size: 11px;\n"
"        selection-background-color: #F8E2E6;\n"
"        selection-color: #3D2619;\n"
"    }\n"
"    QHeaderView::section {\n"
"        background-color: #FFF7F2;\n"
"        color: #633927;\n"
"        font-weight: bold;\n"
"        border: none;\n"
"        border-bottom: 2px solid #EEDCD0;\n"
"        padding: 8px 6px;\n"
"        font-size: 11px;\n"
"    }\n"
"    QPushButton.actionBtn {\n"
"        background-color: #633927;\n"
"        color: #FFFFFF;\n"
"        border-radius: 8px;\n"
"        font-weight: bold;\n"
"        font-size: 11px;\n"
"        padding: 8px 14px;\n"
"        border: none;\n"
"    }\n"
"    QPushButton.actionBtn:hover {\n"
"        background-color: #4D2B1D;\n"
"    }\n"
"    QPushButton.secondaryBtn {\n"
"        background-color: #FFFFFF;\n"
"        color: #633927;\n"
"        border: 1.5px solid #633927;\n"
"        border-radius: 8px;\n"
"        font-weight: bold;\n"
"        font-size: 11px;\n"
"        padding: 7px 12px;\n"
"    }\n"
""
                        "    QPushButton.secondaryBtn:hover {\n"
"        background-color: #FFF7F2;\n"
"    }\n"
"    QLabel.formTag {\n"
"        background-color: #633927;\n"
"        color: #FFFFFF;\n"
"        border-radius: 6px;\n"
"        font-weight: bold;\n"
"        font-size: 10px;\n"
"        padding: 4px 8px;\n"
"        min-width: 95px;\n"
"    }\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainHLayout = new QHBoxLayout(centralwidget);
        mainHLayout->setSpacing(12);
        mainHLayout->setObjectName("mainHLayout");
        mainHLayout->setContentsMargins(12, 12, 12, 12);
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(190, 0));
        sidebarFrame->setMaximumSize(QSize(200, 16777215));
        sidebarVLayout = new QVBoxLayout(sidebarFrame);
        sidebarVLayout->setSpacing(9);
        sidebarVLayout->setObjectName("sidebarVLayout");
        sidebarVLayout->setContentsMargins(12, 14, 12, 14);
        labelLogo = new QLabel(sidebarFrame);
        labelLogo->setObjectName("labelLogo");
        labelLogo->setMinimumSize(QSize(160, 115));
        labelLogo->setMaximumSize(QSize(180, 130));
        labelLogo->setPixmap(QPixmap(QString::fromUtf8(":/resources/logo.png")));
        labelLogo->setScaledContents(true);
        labelLogo->setAlignment(Qt::AlignCenter);

        sidebarVLayout->addWidget(labelLogo);

        spacerLogo = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        sidebarVLayout->addItem(spacerLogo);

        btnNavAnimaux = new QPushButton(sidebarFrame);
        btnNavAnimaux->setObjectName("btnNavAnimaux");

        sidebarVLayout->addWidget(btnNavAnimaux);

        btnNavProprietaires = new QPushButton(sidebarFrame);
        btnNavProprietaires->setObjectName("btnNavProprietaires");

        sidebarVLayout->addWidget(btnNavProprietaires);

        btnNavSoins = new QPushButton(sidebarFrame);
        btnNavSoins->setObjectName("btnNavSoins");

        sidebarVLayout->addWidget(btnNavSoins);

        btnNavCommandes = new QPushButton(sidebarFrame);
        btnNavCommandes->setObjectName("btnNavCommandes");

        sidebarVLayout->addWidget(btnNavCommandes);

        btnNavProduits = new QPushButton(sidebarFrame);
        btnNavProduits->setObjectName("btnNavProduits");

        sidebarVLayout->addWidget(btnNavProduits);

        btnNavPaiements = new QPushButton(sidebarFrame);
        btnNavPaiements->setObjectName("btnNavPaiements");

        sidebarVLayout->addWidget(btnNavPaiements);

        sidebarSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarVLayout->addItem(sidebarSpacer);

        btnNavParametre = new QPushButton(sidebarFrame);
        btnNavParametre->setObjectName("btnNavParametre");

        sidebarVLayout->addWidget(btnNavParametre);

        btnNavAide = new QPushButton(sidebarFrame);
        btnNavAide->setObjectName("btnNavAide");

        sidebarVLayout->addWidget(btnNavAide);


        mainHLayout->addWidget(sidebarFrame);

        centerVLayout = new QVBoxLayout();
        centerVLayout->setSpacing(10);
        centerVLayout->setObjectName("centerVLayout");
        lblTitle = new QLabel(centralwidget);
        lblTitle->setObjectName("lblTitle");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        font.setBold(true);
        lblTitle->setFont(font);
        lblTitle->setStyleSheet(QString::fromUtf8("color: #3D2619;"));

        centerVLayout->addWidget(lblTitle);

        lblSubtitle = new QLabel(centralwidget);
        lblSubtitle->setObjectName("lblSubtitle");
        lblSubtitle->setStyleSheet(QString::fromUtf8("color: #7D6658; font-size: 11px; margin-bottom: 2px;"));

        centerVLayout->addWidget(lblSubtitle);

        searchHLayout = new QHBoxLayout();
        searchHLayout->setSpacing(8);
        searchHLayout->setObjectName("searchHLayout");
        inputSearch = new QLineEdit(centralwidget);
        inputSearch->setObjectName("inputSearch");
        inputSearch->setClearButtonEnabled(true);

        searchHLayout->addWidget(inputSearch);

        comboFilterType = new QComboBox(centralwidget);
        comboFilterType->addItem(QString());
        comboFilterType->addItem(QString());
        comboFilterType->addItem(QString());
        comboFilterType->addItem(QString());
        comboFilterType->addItem(QString());
        comboFilterType->addItem(QString());
        comboFilterType->setObjectName("comboFilterType");
        comboFilterType->setMinimumSize(QSize(150, 0));

        searchHLayout->addWidget(comboFilterType);


        centerVLayout->addLayout(searchHLayout);

        toolsHLayout = new QHBoxLayout();
        toolsHLayout->setSpacing(8);
        toolsHLayout->setObjectName("toolsHLayout");
        lblListTitle = new QLabel(centralwidget);
        lblListTitle->setObjectName("lblListTitle");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(13);
        font1.setBold(true);
        lblListTitle->setFont(font1);
        lblListTitle->setStyleSheet(QString::fromUtf8("color: #5C3826;"));

        toolsHLayout->addWidget(lblListTitle);

        toolsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        toolsHLayout->addItem(toolsSpacer);

        btnTrierPrix = new QPushButton(centralwidget);
        btnTrierPrix->setObjectName("btnTrierPrix");
        btnTrierPrix->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        toolsHLayout->addWidget(btnTrierPrix);

        btnTrierDate = new QPushButton(centralwidget);
        btnTrierDate->setObjectName("btnTrierDate");
        btnTrierDate->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        toolsHLayout->addWidget(btnTrierDate);

        btnExportPdf = new QPushButton(centralwidget);
        btnExportPdf->setObjectName("btnExportPdf");
        btnExportPdf->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnExportPdf->setStyleSheet(QString::fromUtf8("\n"
"            background-color: #FCE4E8;\n"
"            color: #633927;\n"
"            border: 1.5px solid #F6A5B5;\n"
"            border-radius: 8px;\n"
"            font-weight: bold;\n"
"            font-size: 11px;\n"
"            padding: 7px 12px;\n"
"           "));

        toolsHLayout->addWidget(btnExportPdf);


        centerVLayout->addLayout(toolsHLayout);

        tableCommandes = new QTableWidget(centralwidget);
        if (tableCommandes->columnCount() < 6)
            tableCommandes->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableCommandes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableCommandes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableCommandes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableCommandes->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableCommandes->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableCommandes->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableCommandes->setObjectName("tableCommandes");
        tableCommandes->setAlternatingRowColors(true);
        tableCommandes->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableCommandes->setSelectionMode(QAbstractItemView::SingleSelection);
        tableCommandes->setShowGrid(false);
        tableCommandes->setSortingEnabled(false);
        tableCommandes->horizontalHeader()->setStretchLastSection(true);

        centerVLayout->addWidget(tableCommandes);

        bottomHLayout = new QHBoxLayout();
        bottomHLayout->setSpacing(12);
        bottomHLayout->setObjectName("bottomHLayout");
        statsFrame = new QFrame(centralwidget);
        statsFrame->setObjectName("statsFrame");
        statsVLayout = new QVBoxLayout(statsFrame);
        statsVLayout->setObjectName("statsVLayout");
        statsVLayout->setContentsMargins(12, 10, 12, 10);
        lblStatsTitle = new QLabel(statsFrame);
        lblStatsTitle->setObjectName("lblStatsTitle");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(11);
        font2.setBold(true);
        lblStatsTitle->setFont(font2);
        lblStatsTitle->setStyleSheet(QString::fromUtf8("color: #5C3826;"));

        statsVLayout->addWidget(lblStatsTitle);

        widgetCurve = new CurveStatsWidget(statsFrame);
        widgetCurve->setObjectName("widgetCurve");
        widgetCurve->setMinimumSize(QSize(0, 160));

        statsVLayout->addWidget(widgetCurve);


        bottomHLayout->addWidget(statsFrame);

        alertFrame = new QFrame(centralwidget);
        alertFrame->setObjectName("alertFrame");
        alertFrame->setMaximumSize(QSize(250, 16777215));
        alertFrame->setStyleSheet(QString::fromUtf8("\n"
"            QFrame#alertFrame {\n"
"                background-color: #FFFFFF;\n"
"                border: 1.5px solid #F6A5B5;\n"
"                border-radius: 14px;\n"
"            }\n"
"           "));
        alertVLayout = new QVBoxLayout(alertFrame);
        alertVLayout->setObjectName("alertVLayout");
        alertVLayout->setContentsMargins(14, 14, 14, 14);
        lblAlertHeading = new QLabel(alertFrame);
        lblAlertHeading->setObjectName("lblAlertHeading");
        lblAlertHeading->setAlignment(Qt::AlignCenter);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(12);
        font3.setBold(true);
        lblAlertHeading->setFont(font3);
        lblAlertHeading->setStyleSheet(QString::fromUtf8("color: #D3455B;"));

        alertVLayout->addWidget(lblAlertHeading);

        lblAlertBadge = new QLabel(alertFrame);
        lblAlertBadge->setObjectName("lblAlertBadge");
        lblAlertBadge->setAlignment(Qt::AlignCenter);
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(28);
        font4.setBold(true);
        lblAlertBadge->setFont(font4);
        lblAlertBadge->setStyleSheet(QString::fromUtf8("color: #D3455B;"));

        alertVLayout->addWidget(lblAlertBadge);

        lblAlertDesc = new QLabel(alertFrame);
        lblAlertDesc->setObjectName("lblAlertDesc");
        lblAlertDesc->setAlignment(Qt::AlignCenter);
        lblAlertDesc->setStyleSheet(QString::fromUtf8("color: #7D6658; font-size: 11px;"));

        alertVLayout->addWidget(lblAlertDesc);

        lblTotalMontant = new QLabel(alertFrame);
        lblTotalMontant->setObjectName("lblTotalMontant");
        lblTotalMontant->setAlignment(Qt::AlignCenter);
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(10);
        font5.setBold(true);
        lblTotalMontant->setFont(font5);
        lblTotalMontant->setStyleSheet(QString::fromUtf8("\n"
"                background-color: #F8EEE6;\n"
"                color: #5C3826;\n"
"                padding: 6px;\n"
"                border-radius: 6px;\n"
"              "));

        alertVLayout->addWidget(lblTotalMontant);


        bottomHLayout->addWidget(alertFrame);


        centerVLayout->addLayout(bottomHLayout);


        mainHLayout->addLayout(centerVLayout);

        formFrame = new QFrame(centralwidget);
        formFrame->setObjectName("formFrame");
        formFrame->setMinimumSize(QSize(310, 0));
        formFrame->setMaximumSize(QSize(330, 16777215));
        formFrame->setStyleSheet(QString::fromUtf8("\n"
"        QFrame#formFrame {\n"
"            background-color: #FFFFFF;\n"
"            border: 1px solid #EFE4DC;\n"
"            border-radius: 16px;\n"
"        }\n"
"       "));
        formVLayout = new QVBoxLayout(formFrame);
        formVLayout->setSpacing(9);
        formVLayout->setObjectName("formVLayout");
        formVLayout->setContentsMargins(14, 14, 14, 14);
        lblFormBanner = new QLabel(formFrame);
        lblFormBanner->setObjectName("lblFormBanner");
        lblFormBanner->setAlignment(Qt::AlignCenter);
        lblFormBanner->setFont(font3);
        lblFormBanner->setStyleSheet(QString::fromUtf8("\n"
"            background-color: #633927;\n"
"            color: #FFFFFF;\n"
"            padding: 10px;\n"
"            border-radius: 8px;\n"
"          "));

        formVLayout->addWidget(lblFormBanner);

        lblFormCircle = new QLabel(formFrame);
        lblFormCircle->setObjectName("lblFormCircle");
        lblFormCircle->setMinimumSize(QSize(60, 60));
        lblFormCircle->setMaximumSize(QSize(60, 60));
        lblFormCircle->setAlignment(Qt::AlignCenter);
        QFont font6;
        font6.setPointSize(22);
        lblFormCircle->setFont(font6);
        lblFormCircle->setStyleSheet(QString::fromUtf8("\n"
"            border: 2px solid #D9C3B5;\n"
"            border-radius: 30px;\n"
"            background-color: #FFFDF9;\n"
"          "));

        formVLayout->addWidget(lblFormCircle);

        rowIdLayout = new QHBoxLayout();
        rowIdLayout->setObjectName("rowIdLayout");
        tagId = new QLabel(formFrame);
        tagId->setObjectName("tagId");

        rowIdLayout->addWidget(tagId);

        txtId = new QLineEdit(formFrame);
        txtId->setObjectName("txtId");

        rowIdLayout->addWidget(txtId);


        formVLayout->addLayout(rowIdLayout);

        rowDateLayout = new QHBoxLayout();
        rowDateLayout->setObjectName("rowDateLayout");
        tagDate = new QLabel(formFrame);
        tagDate->setObjectName("tagDate");

        rowDateLayout->addWidget(tagDate);

        dateLivraison = new QDateEdit(formFrame);
        dateLivraison->setObjectName("dateLivraison");
        dateLivraison->setCalendarPopup(true);

        rowDateLayout->addWidget(dateLivraison);


        formVLayout->addLayout(rowDateLayout);

        rowMontantLayout = new QHBoxLayout();
        rowMontantLayout->setObjectName("rowMontantLayout");
        tagMontant = new QLabel(formFrame);
        tagMontant->setObjectName("tagMontant");

        rowMontantLayout->addWidget(tagMontant);

        spinMontant = new QDoubleSpinBox(formFrame);
        spinMontant->setObjectName("spinMontant");
        spinMontant->setMaximum(999999.989999999990687);
        spinMontant->setSingleStep(10.000000000000000);

        rowMontantLayout->addWidget(spinMontant);


        formVLayout->addLayout(rowMontantLayout);

        rowTypeLayout = new QHBoxLayout();
        rowTypeLayout->setObjectName("rowTypeLayout");
        tagType = new QLabel(formFrame);
        tagType->setObjectName("tagType");

        rowTypeLayout->addWidget(tagType);

        comboType = new QComboBox(formFrame);
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->addItem(QString());
        comboType->setObjectName("comboType");

        rowTypeLayout->addWidget(comboType);


        formVLayout->addLayout(rowTypeLayout);

        rowQteLayout = new QHBoxLayout();
        rowQteLayout->setObjectName("rowQteLayout");
        tagQte = new QLabel(formFrame);
        tagQte->setObjectName("tagQte");

        rowQteLayout->addWidget(tagQte);

        spinQuantite = new QSpinBox(formFrame);
        spinQuantite->setObjectName("spinQuantite");
        spinQuantite->setMaximum(99999);
        spinQuantite->setValue(1);

        rowQteLayout->addWidget(spinQuantite);


        formVLayout->addLayout(rowQteLayout);

        rowEtatLayout = new QHBoxLayout();
        rowEtatLayout->setObjectName("rowEtatLayout");
        tagEtat = new QLabel(formFrame);
        tagEtat->setObjectName("tagEtat");

        rowEtatLayout->addWidget(tagEtat);

        comboEtat = new QComboBox(formFrame);
        comboEtat->addItem(QString());
        comboEtat->addItem(QString());
        comboEtat->addItem(QString());
        comboEtat->addItem(QString());
        comboEtat->addItem(QString());
        comboEtat->setObjectName("comboEtat");

        rowEtatLayout->addWidget(comboEtat);


        formVLayout->addLayout(rowEtatLayout);

        formSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formVLayout->addItem(formSpacer);

        buttonsGrid = new QGridLayout();
        buttonsGrid->setObjectName("buttonsGrid");
        btnAjouter = new QPushButton(formFrame);
        btnAjouter->setObjectName("btnAjouter");
        btnAjouter->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsGrid->addWidget(btnAjouter, 0, 0, 1, 1);

        btnModifier = new QPushButton(formFrame);
        btnModifier->setObjectName("btnModifier");
        btnModifier->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsGrid->addWidget(btnModifier, 0, 1, 1, 1);

        btnSupprimer = new QPushButton(formFrame);
        btnSupprimer->setObjectName("btnSupprimer");
        btnSupprimer->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnSupprimer->setStyleSheet(QString::fromUtf8("\n"
"                background-color: #FFF0F2;\n"
"                color: #C0392B;\n"
"                border: 1.5px solid #F6A5B5;\n"
"                border-radius: 8px;\n"
"                font-weight: bold;\n"
"                font-size: 11px;\n"
"                padding: 7px 12px;\n"
"            "));

        buttonsGrid->addWidget(btnSupprimer, 1, 0, 1, 1);

        btnVider = new QPushButton(formFrame);
        btnVider->setObjectName("btnVider");
        btnVider->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        buttonsGrid->addWidget(btnVider, 1, 1, 1, 1);


        formVLayout->addLayout(buttonsGrid);


        mainHLayout->addWidget(formFrame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Pawch\303\251 - Gestion des Commandes Fournisseurs", nullptr));
        labelLogo->setText(QString());
        btnNavAnimaux->setText(QCoreApplication::translate("MainWindow", "Gestion Animaux", nullptr));
        btnNavAnimaux->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavProprietaires->setText(QCoreApplication::translate("MainWindow", "Gestion Propri\303\251taires", nullptr));
        btnNavProprietaires->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavSoins->setText(QCoreApplication::translate("MainWindow", "Consultations et Soins", nullptr));
        btnNavSoins->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavCommandes->setText(QCoreApplication::translate("MainWindow", "Commandes Fournisseurs", nullptr));
        btnNavCommandes->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButtonActive", nullptr)));
        btnNavProduits->setText(QCoreApplication::translate("MainWindow", "Produits et Accessoires", nullptr));
        btnNavProduits->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavPaiements->setText(QCoreApplication::translate("MainWindow", "Paiements et Factures", nullptr));
        btnNavPaiements->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavParametre->setText(QCoreApplication::translate("MainWindow", "\342\232\231 Param\303\250tre", nullptr));
        btnNavParametre->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavAide->setText(QCoreApplication::translate("MainWindow", "? Aide", nullptr));
        btnNavAide->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        lblTitle->setText(QCoreApplication::translate("MainWindow", "Commandes Fournisseurs", nullptr));
        lblSubtitle->setText(QCoreApplication::translate("MainWindow", "G\303\251rez les commandes fournisseurs, approvisionnements et livraisons", nullptr));
        inputSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher par type de produit (ex: Alimentation, Soin...)", nullptr));
        comboFilterType->setItemText(0, QCoreApplication::translate("MainWindow", "Tous les types", nullptr));
        comboFilterType->setItemText(1, QCoreApplication::translate("MainWindow", "Alimentation", nullptr));
        comboFilterType->setItemText(2, QCoreApplication::translate("MainWindow", "Soin & Sant\303\251", nullptr));
        comboFilterType->setItemText(3, QCoreApplication::translate("MainWindow", "Accessoire", nullptr));
        comboFilterType->setItemText(4, QCoreApplication::translate("MainWindow", "Hygi\303\250ne", nullptr));
        comboFilterType->setItemText(5, QCoreApplication::translate("MainWindow", "\303\211quipement", nullptr));

        lblListTitle->setText(QCoreApplication::translate("MainWindow", "Liste des Commandes", nullptr));
        btnTrierPrix->setText(QCoreApplication::translate("MainWindow", "\342\206\225 Trier par prix", nullptr));
        btnTrierPrix->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
        btnTrierDate->setText(QCoreApplication::translate("MainWindow", "\360\237\223\205 Trier par date", nullptr));
        btnTrierDate->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
        btnExportPdf->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Exporter PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableCommandes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID Commande", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableCommandes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Date livraison", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableCommandes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Montant (DT)", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableCommandes->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type produit", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableCommandes->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableCommandes->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\303\211tat", nullptr));
        statsFrame->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "cardFrame", nullptr)));
        lblStatsTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\210 Statistiques des commandes selon statut (Courbe)", nullptr));
        lblAlertHeading->setText(QCoreApplication::translate("MainWindow", "Alerte Commandes !", nullptr));
        lblAlertBadge->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        lblAlertDesc->setText(QCoreApplication::translate("MainWindow", "commandes en attente \342\232\240\357\270\217", nullptr));
        lblTotalMontant->setText(QCoreApplication::translate("MainWindow", "Total: 1,450.00 DT", nullptr));
        lblFormBanner->setText(QCoreApplication::translate("MainWindow", "+ Commande Fournisseur", nullptr));
        lblFormCircle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246", nullptr));
        tagId->setText(QCoreApplication::translate("MainWindow", "ID Commande :", nullptr));
        tagId->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        txtId->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: CMD-2026-01", nullptr));
        tagDate->setText(QCoreApplication::translate("MainWindow", "Date livraison :", nullptr));
        tagDate->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagMontant->setText(QCoreApplication::translate("MainWindow", "Montant (DT) :", nullptr));
        tagMontant->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagType->setText(QCoreApplication::translate("MainWindow", "Type produit :", nullptr));
        tagType->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        comboType->setItemText(0, QCoreApplication::translate("MainWindow", "Alimentation", nullptr));
        comboType->setItemText(1, QCoreApplication::translate("MainWindow", "Soin & Sant\303\251", nullptr));
        comboType->setItemText(2, QCoreApplication::translate("MainWindow", "Accessoire", nullptr));
        comboType->setItemText(3, QCoreApplication::translate("MainWindow", "Hygi\303\250ne", nullptr));
        comboType->setItemText(4, QCoreApplication::translate("MainWindow", "\303\211quipement", nullptr));

        tagQte->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 :", nullptr));
        tagQte->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagEtat->setText(QCoreApplication::translate("MainWindow", "\303\211tat :", nullptr));
        tagEtat->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        comboEtat->setItemText(0, QCoreApplication::translate("MainWindow", "En attente", nullptr));
        comboEtat->setItemText(1, QCoreApplication::translate("MainWindow", "Confirm\303\251e", nullptr));
        comboEtat->setItemText(2, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        comboEtat->setItemText(3, QCoreApplication::translate("MainWindow", "Livr\303\251e", nullptr));
        comboEtat->setItemText(4, QCoreApplication::translate("MainWindow", "Annul\303\251e", nullptr));

        btnAjouter->setText(QCoreApplication::translate("MainWindow", "+ Ajouter", nullptr));
        btnAjouter->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "actionBtn", nullptr)));
        btnModifier->setText(QCoreApplication::translate("MainWindow", "\342\234\217 Modifier", nullptr));
        btnModifier->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
        btnSupprimer->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221 Supprimer", nullptr));
        btnVider->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Vider", nullptr));
        btnVider->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
