/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame_2;
    QFrame *frame_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_date;
    QLineEdit *lineEdit_montant;
    QLineEdit *lineEdit_type;
    QLineEdit *lineEdit_qte;
    QLineEdit *lineEdit_etat;
    QPushButton *btn_modifier;
    QPushButton *btn_vider;
    QPushButton *btn_enregistrer;
    QPushButton *btn_ajouter;
    QLineEdit *lineEdit_recherche;
    QPushButton *btn_exporter_pdf;
    QFrame *frame_4;
    QTableWidget *tableWidget_commandes;
    QFrame *frame_5;
    QFrame *frame_7;
    QFrame *frame_8;
    QLabel *label_29;
    QFrame *frame_9;
    QFrame *frame_10;
    QFrame *frame_11;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_30;
    QLabel *label_pct_livrees;
    QLabel *label_pct_validees;
    QLabel *label_pct_attente;
    QComboBox *comboBox_tri;
    QFrame *frame;
    QLabel *label_logo;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLabel *label_14;
    QLabel *label_28;
    QLabel *label_27;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1300, 750);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"QMainWindow, QWidget {\n"
"    background-color: #FBF4EE;\n"
"    color: #6B3F2E;\n"
"    font-family: \"Sans-serif\";\n"
"}\n"
"\n"
"\n"
"#frame {\n"
"    background-color: #FFF9F4;\n"
"    border-right: 1px solid #F9DEE4;\n"
"}                                                                                                                                           QPushButton {\n"
"    background-color: transparent;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-size: 14px;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #F9DEE4; /* Rose clair */\n"
"}\n"
"\n"
"\n"
"QPushButton:checked, QPushButton:pressed {\n"
"    background-color: #E77C8D; /* Rose principale */\n"
"    color: #FFF9F4;\n"
"}      "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #F9DEE4;\n"
"    color: #6B3F2E;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding-left: 15px;\n"
"    font-size: 14px;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #E77C8D; /* Rose principal */\n"
"    color: #FFF9F4;\n"
"}\n"
"\n"
"\n"
"QPushButton:checked, QPushButton:pressed {\n"
"    background-color: #E77C8D;\n"
"    color: #FFF9F4;\n"
"}"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(280, 50, 1041, 671));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 0, 311, 651));
        frame_3->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QFrame#frame_3 {\n"
"    background-color: #EBD5C9;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #D9BCB0;\n"
"}\n"
"\n"
"\n"
"QLineEdit {\n"
"    background-color: #FFF9F4;\n"
"    color: #6B3F2E;\n"
"    border: 1px solid #C4A493;\n"
"    border-radius: 6px;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #6B3F2E;\n"
"    color: #FFF9F4;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #8C5542;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #4A2B1F;\n"
"}"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 110, 41, 20));
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 160, 111, 20));
        label_6 = new QLabel(frame_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 210, 63, 20));
        label_7 = new QLabel(frame_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 260, 121, 20));
        label_8 = new QLabel(frame_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 310, 63, 20));
        label_9 = new QLabel(frame_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 360, 51, 20));
        lineEdit_id = new QLineEdit(frame_3);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(150, 110, 113, 26));
        lineEdit_date = new QLineEdit(frame_3);
        lineEdit_date->setObjectName("lineEdit_date");
        lineEdit_date->setGeometry(QRect(150, 160, 113, 26));
        lineEdit_montant = new QLineEdit(frame_3);
        lineEdit_montant->setObjectName("lineEdit_montant");
        lineEdit_montant->setGeometry(QRect(150, 210, 113, 26));
        lineEdit_type = new QLineEdit(frame_3);
        lineEdit_type->setObjectName("lineEdit_type");
        lineEdit_type->setGeometry(QRect(150, 260, 113, 26));
        lineEdit_qte = new QLineEdit(frame_3);
        lineEdit_qte->setObjectName("lineEdit_qte");
        lineEdit_qte->setGeometry(QRect(150, 310, 113, 26));
        lineEdit_etat = new QLineEdit(frame_3);
        lineEdit_etat->setObjectName("lineEdit_etat");
        lineEdit_etat->setGeometry(QRect(150, 360, 113, 26));
        btn_modifier = new QPushButton(frame_3);
        btn_modifier->setObjectName("btn_modifier");
        btn_modifier->setGeometry(QRect(100, 430, 101, 41));
        btn_vider = new QPushButton(frame_3);
        btn_vider->setObjectName("btn_vider");
        btn_vider->setGeometry(QRect(170, 500, 101, 41));
        btn_enregistrer = new QPushButton(frame_3);
        btn_enregistrer->setObjectName("btn_enregistrer");
        btn_enregistrer->setGeometry(QRect(30, 500, 101, 41));
        btn_ajouter = new QPushButton(frame_3);
        btn_ajouter->setObjectName("btn_ajouter");
        btn_ajouter->setGeometry(QRect(40, 30, 201, 41));
        lineEdit_recherche = new QLineEdit(frame_2);
        lineEdit_recherche->setObjectName("lineEdit_recherche");
        lineEdit_recherche->setGeometry(QRect(350, 20, 291, 41));
        btn_exporter_pdf = new QPushButton(frame_2);
        btn_exporter_pdf->setObjectName("btn_exporter_pdf");
        btn_exporter_pdf->setGeometry(QRect(770, 20, 201, 41));
        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(330, 90, 681, 291));
        frame_4->setStyleSheet(QString::fromUtf8("QFrame#frame_4 {\n"
"    background-color:#E77C8D;\n"
"    border-radius: 10px;\n"
"}"));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        tableWidget_commandes = new QTableWidget(frame_4);
        if (tableWidget_commandes->columnCount() < 6)
            tableWidget_commandes->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_commandes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_commandes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_commandes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_commandes->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_commandes->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_commandes->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget_commandes->rowCount() < 4)
            tableWidget_commandes->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_commandes->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_commandes->setItem(0, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_commandes->setItem(0, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_commandes->setItem(0, 3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_commandes->setItem(0, 4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_commandes->setItem(0, 5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_commandes->setItem(1, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_commandes->setItem(1, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_commandes->setItem(1, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_commandes->setItem(1, 3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_commandes->setItem(1, 4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_commandes->setItem(1, 5, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_commandes->setItem(2, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_commandes->setItem(2, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_commandes->setItem(2, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_commandes->setItem(2, 3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_commandes->setItem(2, 4, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_commandes->setItem(2, 5, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_commandes->setItem(3, 0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_commandes->setItem(3, 1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_commandes->setItem(3, 2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_commandes->setItem(3, 3, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_commandes->setItem(3, 4, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_commandes->setItem(3, 5, __qtablewidgetitem29);
        tableWidget_commandes->setObjectName("tableWidget_commandes");
        tableWidget_commandes->setGeometry(QRect(20, 20, 641, 251));
        tableWidget_commandes->setRowCount(4);
        tableWidget_commandes->setColumnCount(6);
        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(410, 410, 491, 241));
        frame_5->setStyleSheet(QString::fromUtf8("QFrame#frame_5 {\n"
"    background-color: #EBD5C9;\n"
"    border-radius: 10px;\n"
"}"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        frame_7 = new QFrame(frame_5);
        frame_7->setObjectName("frame_7");
        frame_7->setGeometry(QRect(100, 180, 281, 6));
        frame_7->setStyleSheet(QString::fromUtf8("/* Bech tna7i el 5alfeiya wel border mta3 el frame w t5alliha ken ligne */\n"
"background-color: transparent;\n"
"border: none;\n"
"/* Zid border bottom mte3 2px */\n"
"border-bottom: 2px solid #6B3F2E;\n"
"/* 5ali el height mte3ou s8ir barcha */\n"
"max-height: 4px;\n"
"min-height: 4px;\n"
"margin: 0px;"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        frame_8 = new QFrame(frame_5);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(100, 90, 6, 94));
        frame_8->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"border-left: 2px solid #6B3F2E;\n"
"max-width: 4px;\n"
"min-width: 4px;\n"
"margin: 0px;"));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        label_29 = new QLabel(frame_5);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(130, 20, 321, 31));
        frame_9 = new QFrame(frame_5);
        frame_9->setObjectName("frame_9");
        frame_9->setGeometry(QRect(130, 90, 31, 91));
        frame_9->setStyleSheet(QString::fromUtf8("background-color: #6B3F2E;"));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        frame_10 = new QFrame(frame_5);
        frame_10->setObjectName("frame_10");
        frame_10->setGeometry(QRect(290, 150, 31, 31));
        frame_10->setStyleSheet(QString::fromUtf8("background-color: #FFFACD;"));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        frame_11 = new QFrame(frame_5);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(210, 120, 31, 61));
        frame_11->setStyleSheet(QString::fromUtf8("background-color: #E77C8D;"));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        label_31 = new QLabel(frame_5);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(200, 200, 71, 20));
        label_32 = new QLabel(frame_5);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(280, 200, 71, 20));
        label_33 = new QLabel(frame_5);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, 10, 111, 21));
        label_30 = new QLabel(frame_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(120, 200, 51, 21));
        label_pct_livrees = new QLabel(frame_5);
        label_pct_livrees->setObjectName("label_pct_livrees");
        label_pct_livrees->setGeometry(QRect(120, 60, 41, 21));
        label_pct_validees = new QLabel(frame_5);
        label_pct_validees->setObjectName("label_pct_validees");
        label_pct_validees->setGeometry(QRect(200, 60, 41, 21));
        label_pct_attente = new QLabel(frame_5);
        label_pct_attente->setObjectName("label_pct_attente");
        label_pct_attente->setGeometry(QRect(280, 60, 41, 21));
        comboBox_tri = new QComboBox(frame_2);
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->addItem(QString());
        comboBox_tri->setObjectName("comboBox_tri");
        comboBox_tri->setGeometry(QRect(660, 20, 91, 41));
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, -20, 250, 721));
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: #FBF4EE;\n"
"    border: none;\n"
"}"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_logo = new QLabel(frame);
        label_logo->setObjectName("label_logo");
        label_logo->setGeometry(QRect(20, 40, 201, 141));
        label_logo->setPixmap(QPixmap(QString::fromUtf8(":/photo.jpeg")));
        label_logo->setScaledContents(true);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 500, 161, 41));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(40, 200, 161, 41));
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(40, 260, 161, 41));
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(40, 320, 161, 41));
        pushButton_6 = new QPushButton(frame);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(40, 380, 161, 41));
        pushButton_7 = new QPushButton(frame);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(40, 440, 161, 41));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(300, -10, 701, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sans-serif")});
        font.setPointSize(18);
        font.setBold(true);
        label_14->setFont(font);
        label_28 = new QLabel(centralwidget);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(1230, 0, 41, 31));
        label_28->setPixmap(QPixmap(QString::fromUtf8("../../Downloads/admin.jpg")));
        label_28->setScaledContents(true);
        label_27 = new QLabel(centralwidget);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(1190, 0, 21, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1300, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Date de livraison:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Montant:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Type de produits:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Etat:", nullptr));
        btn_modifier->setText(QCoreApplication::translate("MainWindow", "Modifier:", nullptr));
        btn_vider->setText(QCoreApplication::translate("MainWindow", "Vider:", nullptr));
        btn_enregistrer->setText(QCoreApplication::translate("MainWindow", "Enregistrer :", nullptr));
        btn_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter une commande:", nullptr));
        lineEdit_recherche->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215Recherche :", nullptr));
        btn_exporter_pdf->setText(QCoreApplication::translate("MainWindow", "Exporter sous forme Pdf :", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_commandes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_commandes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_commandes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_commandes->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_commandes->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_commandes->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Etat", nullptr));

        const bool __sortingEnabled = tableWidget_commandes->isSortingEnabled();
        tableWidget_commandes->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_commandes->item(0, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "CMD001", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_commandes->item(0, 1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "1/10/2026", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_commandes->item(0, 2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "300 DT", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_commandes->item(0, 3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Alimentation", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_commandes->item(0, 4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_commandes->item(0, 5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "en attente", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_commandes->item(1, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "CMD002", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_commandes->item(1, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "25/5/2026", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_commandes->item(1, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "200 DT", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_commandes->item(1, 3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Accessoires", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_commandes->item(1, 4);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_commandes->item(1, 5);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "livr\303\251e", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_commandes->item(2, 0);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "CMD003", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_commandes->item(2, 1);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "30/6/2026", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_commandes->item(2, 2);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "450 DT", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_commandes->item(2, 3);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Soins", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_commandes->item(2, 4);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_commandes->item(2, 5);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "valid\303\251e", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_commandes->item(3, 0);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "CMD004", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_commandes->item(3, 1);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "30/9/2026", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_commandes->item(3, 2);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "400 DT", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_commandes->item(3, 3);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Jouets", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_commandes->item(3, 4);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_commandes->item(3, 5);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "livr\303\251e", nullptr));
        tableWidget_commandes->setSortingEnabled(__sortingEnabled);

        label_29->setText(QCoreApplication::translate("MainWindow", "Repartitipon des commandes selon leurs \303\251tat:", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "Valid\303\251es:", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "En attente:", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "STATISTIQUES:", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "Livr\303\251es:", nullptr));
        label_pct_livrees->setText(QCoreApplication::translate("MainWindow", "100 %", nullptr));
        label_pct_validees->setText(QCoreApplication::translate("MainWindow", "100 %", nullptr));
        label_pct_attente->setText(QCoreApplication::translate("MainWindow", "100 %", nullptr));
        comboBox_tri->setItemText(0, QCoreApplication::translate("MainWindow", "Trier", nullptr));
        comboBox_tri->setItemText(1, QCoreApplication::translate("MainWindow", "Trier par montant", nullptr));
        comboBox_tri->setItemText(2, QCoreApplication::translate("MainWindow", "Trier par date", nullptr));

        label_logo->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217  Parametres", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\360\237\220\261  Animaux", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\222\274  Fournisseurs", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\360\237\251\272  Rendez-vous", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\360\237\233\222  Stock", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246  Commandes", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Gestion des commandes:", nullptr));
        label_28->setText(QString());
        label_27->setText(QCoreApplication::translate("MainWindow", "\360\237\224\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
