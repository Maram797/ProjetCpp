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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainHLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *sidebarVLayout;
    QLabel *labelLogo;
    QPushButton *btnNavAnimaux;
    QPushButton *btnNavCommandes;
    QPushButton *btnNavSoins;
    QPushButton *btnNavProduits;
    QPushButton *btnNavPaiements;
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
    QWidget *widgetCurve;
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
    QHBoxLayout *rowNomLayout;
    QLabel *tagNom;
    QLineEdit *lineEdit;
    QHBoxLayout *rowPrenomLayout;
    QLabel *tagPrenom;
    QLineEdit *lineEdit_2;
    QHBoxLayout *rowTelLayout;
    QLabel *tagTel;
    QLineEdit *lineEdit_3;
    QHBoxLayout *rowMailLayout;
    QLabel *tagMail;
    QLineEdit *lineEdit_4;
    QHBoxLayout *rowAdresseLayout;
    QLabel *tagAdresse;
    QLineEdit *lineEdit_5;
    QHBoxLayout *rowEmbaucheLayout;
    QLabel *tagEmbauche;
    QDateEdit *dateEditEmbauche;
    QHBoxLayout *rowPosteLayout;
    QLabel *tagPoste;
    QComboBox *comboPoste;
    QHBoxLayout *rowNaissanceLayout;
    QLabel *tagNaissance;
    QDateEdit *dateEditNaissance;
    QHBoxLayout *rowPwdLayout;
    QLabel *tagPwd;
    QLineEdit *lineEditMotDePasse;
    QHBoxLayout *rowQuestionLayout;
    QLabel *tagQuestion;
    QComboBox *comboQuestion;
    QHBoxLayout *rowReponseLayout;
    QLabel *tagReponse;
    QLineEdit *lineEditReponse;
    QFrame *qrFrame;
    QVBoxLayout *qrVLayout;
    QLabel *lblQrTitle;
    QLabel *lblQrImage;
    QLabel *lblQrInfo;
    QPushButton *btnSaveQr;
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
        MainWindow->resize(1274, 780);
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
"    QPushButton.navButton[active=\"true\"], QPushButton.navButton[active=\"true\"]:hover {\n"
"        background-color: #633927;\n"
"        border: 1px solid #633927;\n"
"        border-radius: 8px;\n"
"        padding: 9px 12px;\n"
"  "
                        "      text-align: center;\n"
"        color: #FFFFFF;\n"
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
"        co"
                        "lor: #3D2619;\n"
"        font-family: \"Segoe UI\", sans-serif;\n"
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
"        f"
                        "ont-size: 11px;\n"
"        padding: 7px 12px;\n"
"    }\n"
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
        labelLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);

        sidebarVLayout->addWidget(labelLogo);

        btnNavAnimaux = new QPushButton(sidebarFrame);
        btnNavAnimaux->setObjectName("btnNavAnimaux");

        sidebarVLayout->addWidget(btnNavAnimaux);

        btnNavCommandes = new QPushButton(sidebarFrame);
        btnNavCommandes->setObjectName("btnNavCommandes");

        sidebarVLayout->addWidget(btnNavCommandes);

        btnNavSoins = new QPushButton(sidebarFrame);
        btnNavSoins->setObjectName("btnNavSoins");

        sidebarVLayout->addWidget(btnNavSoins);

        btnNavProduits = new QPushButton(sidebarFrame);
        btnNavProduits->setObjectName("btnNavProduits");

        sidebarVLayout->addWidget(btnNavProduits);

        btnNavPaiements = new QPushButton(sidebarFrame);
        btnNavPaiements->setObjectName("btnNavPaiements");

        sidebarVLayout->addWidget(btnNavPaiements);


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
        if (tableCommandes->columnCount() < 5)
            tableCommandes->setColumnCount(5);
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
        tableCommandes->setObjectName("tableCommandes");
        tableCommandes->setAlternatingRowColors(true);
        tableCommandes->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableCommandes->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
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

        widgetCurve = new QWidget(statsFrame);
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
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(12);
        font3.setBold(true);
        lblAlertHeading->setFont(font3);
        lblAlertHeading->setStyleSheet(QString::fromUtf8("color: #D3455B;"));
        lblAlertHeading->setAlignment(Qt::AlignmentFlag::AlignCenter);

        alertVLayout->addWidget(lblAlertHeading);

        lblAlertBadge = new QLabel(alertFrame);
        lblAlertBadge->setObjectName("lblAlertBadge");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(28);
        font4.setBold(true);
        lblAlertBadge->setFont(font4);
        lblAlertBadge->setStyleSheet(QString::fromUtf8("color: #D3455B;"));
        lblAlertBadge->setAlignment(Qt::AlignmentFlag::AlignCenter);

        alertVLayout->addWidget(lblAlertBadge);

        lblAlertDesc = new QLabel(alertFrame);
        lblAlertDesc->setObjectName("lblAlertDesc");
        lblAlertDesc->setStyleSheet(QString::fromUtf8("color: #7D6658; font-size: 11px;"));
        lblAlertDesc->setAlignment(Qt::AlignmentFlag::AlignCenter);

        alertVLayout->addWidget(lblAlertDesc);

        lblTotalMontant = new QLabel(alertFrame);
        lblTotalMontant->setObjectName("lblTotalMontant");
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
        lblTotalMontant->setAlignment(Qt::AlignmentFlag::AlignCenter);

        alertVLayout->addWidget(lblTotalMontant);


        bottomHLayout->addWidget(alertFrame);


        centerVLayout->addLayout(bottomHLayout);


        mainHLayout->addLayout(centerVLayout);

        formFrame = new QFrame(centralwidget);
        formFrame->setObjectName("formFrame");
        formFrame->setMinimumSize(QSize(330, 0));
        formFrame->setMaximumSize(QSize(360, 16777215));
        formFrame->setStyleSheet(QString::fromUtf8("\n"
"        QFrame#formFrame {\n"
"            background-color: #FFFFFF;\n"
"            border: 1px solid #EFE4DC;\n"
"            border-radius: 16px;\n"
"        }\n"
"       "));
        formVLayout = new QVBoxLayout(formFrame);
        formVLayout->setSpacing(6);
        formVLayout->setObjectName("formVLayout");
        formVLayout->setContentsMargins(14, 14, 14, 14);
        lblFormBanner = new QLabel(formFrame);
        lblFormBanner->setObjectName("lblFormBanner");
        lblFormBanner->setFont(font3);
        lblFormBanner->setStyleSheet(QString::fromUtf8("\n"
"            background-color: #633927;\n"
"            color: #FFFFFF;\n"
"            padding: 10px;\n"
"            border-radius: 8px;\n"
"          "));
        lblFormBanner->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formVLayout->addWidget(lblFormBanner);

        lblFormCircle = new QLabel(formFrame);
        lblFormCircle->setObjectName("lblFormCircle");
        lblFormCircle->setMinimumSize(QSize(60, 60));
        lblFormCircle->setMaximumSize(QSize(60, 60));
        QFont font6;
        font6.setPointSize(22);
        lblFormCircle->setFont(font6);
        lblFormCircle->setStyleSheet(QString::fromUtf8("\n"
"            border: 2px solid #D9C3B5;\n"
"            border-radius: 30px;\n"
"            background-color: #FFFDF9;\n"
"          "));
        lblFormCircle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        formVLayout->addWidget(lblFormCircle);

        rowIdLayout = new QHBoxLayout();
        rowIdLayout->setObjectName("rowIdLayout");
        tagId = new QLabel(formFrame);
        tagId->setObjectName("tagId");

        rowIdLayout->addWidget(tagId);

        txtId = new QLineEdit(formFrame);
        txtId->setObjectName("txtId");
        txtId->setReadOnly(true);

        rowIdLayout->addWidget(txtId);


        formVLayout->addLayout(rowIdLayout);

        rowNomLayout = new QHBoxLayout();
        rowNomLayout->setObjectName("rowNomLayout");
        tagNom = new QLabel(formFrame);
        tagNom->setObjectName("tagNom");

        rowNomLayout->addWidget(tagNom);

        lineEdit = new QLineEdit(formFrame);
        lineEdit->setObjectName("lineEdit");

        rowNomLayout->addWidget(lineEdit);


        formVLayout->addLayout(rowNomLayout);

        rowPrenomLayout = new QHBoxLayout();
        rowPrenomLayout->setObjectName("rowPrenomLayout");
        tagPrenom = new QLabel(formFrame);
        tagPrenom->setObjectName("tagPrenom");

        rowPrenomLayout->addWidget(tagPrenom);

        lineEdit_2 = new QLineEdit(formFrame);
        lineEdit_2->setObjectName("lineEdit_2");

        rowPrenomLayout->addWidget(lineEdit_2);


        formVLayout->addLayout(rowPrenomLayout);

        rowTelLayout = new QHBoxLayout();
        rowTelLayout->setObjectName("rowTelLayout");
        tagTel = new QLabel(formFrame);
        tagTel->setObjectName("tagTel");

        rowTelLayout->addWidget(tagTel);

        lineEdit_3 = new QLineEdit(formFrame);
        lineEdit_3->setObjectName("lineEdit_3");

        rowTelLayout->addWidget(lineEdit_3);


        formVLayout->addLayout(rowTelLayout);

        rowMailLayout = new QHBoxLayout();
        rowMailLayout->setObjectName("rowMailLayout");
        tagMail = new QLabel(formFrame);
        tagMail->setObjectName("tagMail");

        rowMailLayout->addWidget(tagMail);

        lineEdit_4 = new QLineEdit(formFrame);
        lineEdit_4->setObjectName("lineEdit_4");

        rowMailLayout->addWidget(lineEdit_4);


        formVLayout->addLayout(rowMailLayout);

        rowAdresseLayout = new QHBoxLayout();
        rowAdresseLayout->setObjectName("rowAdresseLayout");
        tagAdresse = new QLabel(formFrame);
        tagAdresse->setObjectName("tagAdresse");

        rowAdresseLayout->addWidget(tagAdresse);

        lineEdit_5 = new QLineEdit(formFrame);
        lineEdit_5->setObjectName("lineEdit_5");

        rowAdresseLayout->addWidget(lineEdit_5);


        formVLayout->addLayout(rowAdresseLayout);

        rowEmbaucheLayout = new QHBoxLayout();
        rowEmbaucheLayout->setObjectName("rowEmbaucheLayout");
        tagEmbauche = new QLabel(formFrame);
        tagEmbauche->setObjectName("tagEmbauche");

        rowEmbaucheLayout->addWidget(tagEmbauche);

        dateEditEmbauche = new QDateEdit(formFrame);
        dateEditEmbauche->setObjectName("dateEditEmbauche");
        dateEditEmbauche->setCalendarPopup(true);

        rowEmbaucheLayout->addWidget(dateEditEmbauche);


        formVLayout->addLayout(rowEmbaucheLayout);

        rowPosteLayout = new QHBoxLayout();
        rowPosteLayout->setObjectName("rowPosteLayout");
        tagPoste = new QLabel(formFrame);
        tagPoste->setObjectName("tagPoste");

        rowPosteLayout->addWidget(tagPoste);

        comboPoste = new QComboBox(formFrame);
        comboPoste->addItem(QString());
        comboPoste->addItem(QString());
        comboPoste->addItem(QString());
        comboPoste->addItem(QString());
        comboPoste->addItem(QString());
        comboPoste->addItem(QString());
        comboPoste->setObjectName("comboPoste");

        rowPosteLayout->addWidget(comboPoste);


        formVLayout->addLayout(rowPosteLayout);

        rowNaissanceLayout = new QHBoxLayout();
        rowNaissanceLayout->setObjectName("rowNaissanceLayout");
        tagNaissance = new QLabel(formFrame);
        tagNaissance->setObjectName("tagNaissance");

        rowNaissanceLayout->addWidget(tagNaissance);

        dateEditNaissance = new QDateEdit(formFrame);
        dateEditNaissance->setObjectName("dateEditNaissance");
        dateEditNaissance->setCalendarPopup(true);

        rowNaissanceLayout->addWidget(dateEditNaissance);


        formVLayout->addLayout(rowNaissanceLayout);

        rowPwdLayout = new QHBoxLayout();
        rowPwdLayout->setObjectName("rowPwdLayout");
        tagPwd = new QLabel(formFrame);
        tagPwd->setObjectName("tagPwd");

        rowPwdLayout->addWidget(tagPwd);

        lineEditMotDePasse = new QLineEdit(formFrame);
        lineEditMotDePasse->setObjectName("lineEditMotDePasse");
        lineEditMotDePasse->setEchoMode(QLineEdit::EchoMode::Password);

        rowPwdLayout->addWidget(lineEditMotDePasse);


        formVLayout->addLayout(rowPwdLayout);

        rowQuestionLayout = new QHBoxLayout();
        rowQuestionLayout->setObjectName("rowQuestionLayout");
        tagQuestion = new QLabel(formFrame);
        tagQuestion->setObjectName("tagQuestion");

        rowQuestionLayout->addWidget(tagQuestion);

        comboQuestion = new QComboBox(formFrame);
        comboQuestion->addItem(QString());
        comboQuestion->addItem(QString());
        comboQuestion->addItem(QString());
        comboQuestion->addItem(QString());
        comboQuestion->setObjectName("comboQuestion");

        rowQuestionLayout->addWidget(comboQuestion);


        formVLayout->addLayout(rowQuestionLayout);

        rowReponseLayout = new QHBoxLayout();
        rowReponseLayout->setObjectName("rowReponseLayout");
        tagReponse = new QLabel(formFrame);
        tagReponse->setObjectName("tagReponse");

        rowReponseLayout->addWidget(tagReponse);

        lineEditReponse = new QLineEdit(formFrame);
        lineEditReponse->setObjectName("lineEditReponse");

        rowReponseLayout->addWidget(lineEditReponse);


        formVLayout->addLayout(rowReponseLayout);

        qrFrame = new QFrame(formFrame);
        qrFrame->setObjectName("qrFrame");
        qrVLayout = new QVBoxLayout(qrFrame);
        qrVLayout->setSpacing(6);
        qrVLayout->setObjectName("qrVLayout");
        qrVLayout->setContentsMargins(8, 8, 8, 8);
        lblQrTitle = new QLabel(qrFrame);
        lblQrTitle->setObjectName("lblQrTitle");
        lblQrTitle->setFont(font5);
        lblQrTitle->setStyleSheet(QString::fromUtf8("color: #5C3826;"));
        lblQrTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        qrVLayout->addWidget(lblQrTitle);

        lblQrImage = new QLabel(qrFrame);
        lblQrImage->setObjectName("lblQrImage");
        lblQrImage->setMinimumSize(QSize(180, 180));
        lblQrImage->setMaximumSize(QSize(180, 180));
        lblQrImage->setStyleSheet(QString::fromUtf8("\n"
"              background-color: #FFFDF9;\n"
"              border: 1px solid #EFE4DC;\n"
"              border-radius: 8px;\n"
"              color: #A08B7E;\n"
"              font-size: 10px;\n"
"             "));
        lblQrImage->setAlignment(Qt::AlignmentFlag::AlignCenter);

        qrVLayout->addWidget(lblQrImage);

        lblQrInfo = new QLabel(qrFrame);
        lblQrInfo->setObjectName("lblQrInfo");
        lblQrInfo->setStyleSheet(QString::fromUtf8("color: #5C3826; font-size: 10px;"));
        lblQrInfo->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lblQrInfo->setWordWrap(true);

        qrVLayout->addWidget(lblQrInfo);

        btnSaveQr = new QPushButton(qrFrame);
        btnSaveQr->setObjectName("btnSaveQr");
        btnSaveQr->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        qrVLayout->addWidget(btnSaveQr);


        formVLayout->addWidget(qrFrame);

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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Pawch\303\251 - Gestion des Employ\303\251s", nullptr));
        labelLogo->setText(QString());
        btnNavAnimaux->setText(QCoreApplication::translate("MainWindow", "Gestion Animaux", nullptr));
        btnNavAnimaux->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavCommandes->setText(QCoreApplication::translate("MainWindow", "Gestion Employ\303\251s", nullptr));
        btnNavCommandes->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavSoins->setText(QCoreApplication::translate("MainWindow", "Rendez-vous", nullptr));
        btnNavSoins->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavProduits->setText(QCoreApplication::translate("MainWindow", "Gestion Stocks", nullptr));
        btnNavProduits->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        btnNavPaiements->setText(QCoreApplication::translate("MainWindow", "Commandes", nullptr));
        btnNavPaiements->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "navButton", nullptr)));
        lblTitle->setText(QCoreApplication::translate("MainWindow", "Employ\303\251s", nullptr));
        lblSubtitle->setText(QCoreApplication::translate("MainWindow", "G\303\251rez les employ\303\251s, leurs postes et leurs informations personnelles", nullptr));
        inputSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Rechercher par nom, pr\303\251nom, t\303\251l\303\251phone ou e-mail...", nullptr));
        comboFilterType->setItemText(0, QCoreApplication::translate("MainWindow", "Tous les employ\303\251s", nullptr));
        comboFilterType->setItemText(1, QCoreApplication::translate("MainWindow", "Gmail", nullptr));
        comboFilterType->setItemText(2, QCoreApplication::translate("MainWindow", "Outlook", nullptr));
        comboFilterType->setItemText(3, QCoreApplication::translate("MainWindow", "Yahoo", nullptr));
        comboFilterType->setItemText(4, QCoreApplication::translate("MainWindow", "Autres domaines", nullptr));

        lblListTitle->setText(QCoreApplication::translate("MainWindow", "Liste des Employ\303\251s", nullptr));
        btnTrierPrix->setText(QCoreApplication::translate("MainWindow", "\342\206\225 Trier par nom", nullptr));
        btnTrierPrix->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
        btnTrierDate->setText(QCoreApplication::translate("MainWindow", "\360\237\222\274 Trier par poste", nullptr));
        btnTrierDate->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
        btnExportPdf->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Attestation PDF", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableCommandes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID employ\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableCommandes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableCommandes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableCommandes->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableCommandes->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        statsFrame->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "cardFrame", nullptr)));
        lblStatsTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\210 Statistiques par ann\303\251e d'embauche", nullptr));
        lblAlertHeading->setText(QCoreApplication::translate("MainWindow", "Employ\303\251s enregistr\303\251s", nullptr));
        lblAlertBadge->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lblAlertDesc->setText(QCoreApplication::translate("MainWindow", "employ\303\251s enregistr\303\251s", nullptr));
        lblTotalMontant->setText(QCoreApplication::translate("MainWindow", "Avec e-mail : 0", nullptr));
        lblFormBanner->setText(QCoreApplication::translate("MainWindow", "+ Employ\303\251", nullptr));
        lblFormCircle->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        tagId->setText(QCoreApplication::translate("MainWindow", "ID Employ\303\251", nullptr));
        tagId->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        txtId->setPlaceholderText(QCoreApplication::translate("MainWindow", "Auto-g\303\251n\303\251r\303\251", nullptr));
        tagNom->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        tagNom->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagPrenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        tagPrenom->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagTel->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        tagTel->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagMail->setText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        tagMail->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagAdresse->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        tagAdresse->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagEmbauche->setText(QCoreApplication::translate("MainWindow", "Embauche", nullptr));
        tagEmbauche->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        dateEditEmbauche->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
        tagPoste->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        tagPoste->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        comboPoste->setItemText(0, QCoreApplication::translate("MainWindow", "V\303\251t\303\251rinaire", nullptr));
        comboPoste->setItemText(1, QCoreApplication::translate("MainWindow", "Assistant v\303\251t\303\251rinaire", nullptr));
        comboPoste->setItemText(2, QCoreApplication::translate("MainWindow", "Responsable RH", nullptr));
        comboPoste->setItemText(3, QCoreApplication::translate("MainWindow", "Caissier", nullptr));
        comboPoste->setItemText(4, QCoreApplication::translate("MainWindow", "Gestionnaire de stock", nullptr));
        comboPoste->setItemText(5, QCoreApplication::translate("MainWindow", "Administrateur", nullptr));

        tagNaissance->setText(QCoreApplication::translate("MainWindow", "Naissance", nullptr));
        tagNaissance->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        dateEditNaissance->setDisplayFormat(QCoreApplication::translate("MainWindow", "dd/MM/yyyy", nullptr));
        tagPwd->setText(QCoreApplication::translate("MainWindow", "Mot de passe", nullptr));
        tagPwd->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        tagQuestion->setText(QCoreApplication::translate("MainWindow", "Question", nullptr));
        tagQuestion->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        comboQuestion->setItemText(0, QCoreApplication::translate("MainWindow", "Nom de votre premier animal ?", nullptr));
        comboQuestion->setItemText(1, QCoreApplication::translate("MainWindow", "Ville de naissance ?", nullptr));
        comboQuestion->setItemText(2, QCoreApplication::translate("MainWindow", "Nom de votre m\303\250re ?", nullptr));
        comboQuestion->setItemText(3, QCoreApplication::translate("MainWindow", "Plat pr\303\251f\303\251r\303\251 ?", nullptr));

        tagReponse->setText(QCoreApplication::translate("MainWindow", "R\303\251ponse", nullptr));
        tagReponse->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "formTag", nullptr)));
        qrFrame->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "cardFrame", nullptr)));
        lblQrTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\224\263 QR Code Employ\303\251", nullptr));
        lblQrImage->setText(QCoreApplication::translate("MainWindow", "S\303\251lectionnez un employ\303\251", nullptr));
        lblQrInfo->setText(QString());
        btnSaveQr->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 Enregistrer QR", nullptr));
        btnSaveQr->setProperty("class", QVariant(QCoreApplication::translate("MainWindow", "secondaryBtn", nullptr)));
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
