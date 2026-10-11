#include "gestionrendezvous.h"
#include "ui_gestionrendezvous.h"

#include <QAction>
#include <QActionGroup>
#include <QButtonGroup>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QFontMetrics>
#include <QLabel>
#include <QMap>
#include <QPageSize>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QPdfWriter>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSaveFile>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTextEdit>
#include <QTextDocument>
#include <QTimer>
#include <QVBoxLayout>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::ostringstream;
using std::cout;
using std::endl;

class AppointmentChart : public QWidget
{
public:
    explicit AppointmentChart(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setStyleSheet("background: transparent;");
    }

    void setAppointments(const QVector<Patient> &patients)
    {
        QMap<QDate, QPair<int, int>> parDate;
        for (const Patient &patient : patients) {
            auto &compte = parDate[patient.date];
            ++compte.first;
            if (patient.rendezVousRealise)
                ++compte.second;
        }

        m_dates = parDate.keys().toVector();
        m_totaux.clear();
        m_realises.clear();
        for (const QDate &date : qAsConst(m_dates)) {
            m_totaux.append(parDate.value(date).first);
            m_realises.append(parDate.value(date).second);
        }
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        const QRectF plot(30, 5, width() - 45, height() - 22);
        painter.setPen(QPen(QColor("#F3E6DC"), 1));
        painter.drawLine(plot.bottomLeft(), plot.bottomRight());

        if (m_dates.isEmpty())
            return;

        const int maximum = qMax(1, *std::max_element(m_totaux.cbegin(), m_totaux.cend()));
        auto pointAt = [&](int index, int value) {
            const qreal x = m_dates.size() == 1
                ? plot.center().x()
                : plot.left() + plot.width() * index / (m_dates.size() - 1);
            const qreal y = plot.bottom() - plot.height() * value / maximum;
            return QPointF(x, y);
        };
        auto drawSeries = [&](const QVector<int> &values, const QColor &color) {
            QPainterPath path;
            for (int i = 0; i < values.size(); ++i) {
                const QPointF point = pointAt(i, values.at(i));
                if (i == 0)
                    path.moveTo(point);
                else
                    path.lineTo(point);
            }
            painter.setPen(QPen(color, 2));
            painter.setBrush(Qt::NoBrush);
            painter.drawPath(path);
            painter.setBrush(color);
            for (int i = 0; i < values.size(); ++i)
                painter.drawEllipse(pointAt(i, values.at(i)), 3, 3);
        };

        drawSeries(m_totaux, QColor("#A98268"));
        drawSeries(m_realises, QColor("#2E7D46"));

        painter.setPen(QColor("#A98268"));
        const int labelStep = qMax(1, m_dates.size() / 6);
        for (int i = 0; i < m_dates.size(); i += labelStep) {
            const QPointF point = pointAt(i, 0);
            painter.drawText(QRectF(point.x() - 25, plot.bottom() + 3, 50, 16),
                             Qt::AlignHCenter | Qt::AlignTop,
                             m_dates.at(i).toString("dd/MM"));
        }
    }

private:
    QVector<QDate> m_dates;
    QVector<int> m_totaux;
    QVector<int> m_realises;
};

// =====================  CLASSE charte  =====================

charte::charte()
{
    fondPrincipal   = "#FFF9F4";
    fondSidebar     = "#FBF4EE";
    texteBrun       = "#6B3F2E";
    texteSecondaire = "#A98268";
    bordure         = "#F3E6DC";
    survol          = "#F9DEE4";
    accent          = "#E77C8D";
    police          = "Arial";
    tailleTitre     = 20;
    tailleTexte     = 12;
    taillePetit     = 10;
    rayon           = 8;
}

charte::charte(string txt, string fond, string acc)
{
    fondPrincipal   = fond;
    fondSidebar     = "#FBF4EE";
    texteBrun       = txt;
    texteSecondaire = "#A98268";
    bordure         = "#F3E6DC";
    survol          = "#F9DEE4";
    accent          = acc;
    police          = "Arial";
    tailleTitre     = 20;
    tailleTexte     = 12;
    taillePetit     = 10;
    rayon           = 8;
}

charte::charte(string fp, string fs, string tb, string ts, string bd,
               string sv, string ac, string pol, int tt, int tx, int tp, int r)
{
    fondPrincipal = fp;  fondSidebar = fs;  texteBrun = tb;  texteSecondaire = ts;
    bordure = bd;  survol = sv;  accent = ac;  police = pol;
    tailleTitre = tt;  tailleTexte = tx;  taillePetit = tp;  rayon = r;
}

string charte::enTexte(int n) const
{
    ostringstream flux;
    flux << n;
    return flux.str();
}

string charte::couleurStatut(string type, bool fond) const
{
    if (type == "succes") return fond ? "#DDF3E4" : "#2E7D46";
    if (type == "alerte") return fond ? "#FCE1E5" : "#C0394C";
    return fond ? bordure : texteBrun;   // neutre
}

string charte::styleCadre(string nom, string couleurFond) const
{
    return "QFrame#" + nom + " {\n"
                             "    background-color: " + couleurFond + ";\n"
                           "    border: 1px solid " + bordure + ";\n"
                       "    border-radius: " + enTexte(rayon + 2) + "px;\n}";
}

string charte::styleBoutonMenu(string nom) const
{
    return "QPushButton#" + nom + " {\n"
                                  "    background-color: transparent;\n"
                                  "    color: " + texteBrun + ";\n"
                         "    border: none;\n"
                         "    border-radius: " + enTexte(rayon) + "px;\n"
                              "    text-align: left;\n"
                              "    padding-left: 15px;\n"
                              "    font-family: " + police + ";\n"
                      "    font-size: 13px;\n"
                      "    font-weight: bold;\n}\n"
                      "QPushButton#" + nom + ":hover { background-color: " + survol + "; }\n"
                                                            "QPushButton#" + nom + ":pressed { background-color: " + accent + "; color: white; }";
}

string charte::styleBoutonPrincipal(string nom) const
{
    return "QPushButton#" + nom + " {\n"
                                  "    background-color: " + texteBrun + ";\n"
                         "    color: white;\n"
                         "    border: none;\n"
                         "    border-radius: " + enTexte(rayon) + "px;\n"
                              "    font-size: " + enTexte(tailleTexte) + "px;\n"
                                    "    font-weight: bold;\n}\n"
                                    "QPushButton#" + nom + ":hover { background-color: #5A3225; }";
}

string charte::styleLabel(string nom, string type) const
{
    string couleur = texteBrun, gras = "normal";
    int taille = tailleTexte;
    if (type == "titre")           { taille = tailleTitre; gras = "bold"; }
    else if (type == "sous-titre") { couleur = texteSecondaire; taille = taillePetit + 1; }
    else if (type == "section")    { gras = "bold"; }
    else if (type == "rubrique")   { taille = tailleTexte + 2; gras = "bold"; }
    else if (type == "nom")        { taille = tailleTitre - 2; gras = "bold"; }
    else if (type == "valeur")     { taille = tailleTexte + 4; gras = "bold"; }
    else if (type == "texte")      { taille = taillePetit + 1; }
    else if (type == "petit")      { couleur = texteSecondaire; taille = taillePetit; }
    else if (type == "etiquette")  { couleur = texteSecondaire; taille = taillePetit; gras = "bold"; }
    else if (type == "accent")     { couleur = accent; taille = taillePetit + 1; }

    return "QLabel#" + nom + " {\n"
                             "    color: " + couleur + ";\n"
                       "    font-size: " + enTexte(taille) + "px;\n"
                               "    font-weight: " + gras + ";\n"
                    "    background-color: transparent;\n}";
}

string charte::styleStatut(string nom, string type) const
{
    return "QLabel#" + nom + " {\n"
                             "    background-color: " + couleurStatut(type, true) + ";\n"
                                         "    color: " + couleurStatut(type, false) + ";\n"
                                          "    font-size: " + enTexte(taillePetit) + "px;\n"
                                    "    font-weight: bold;\n"
                                    "    border-radius: 10px;\n}";
}

string charte::styleChampTexte(string nom) const
{
    return "QLineEdit#" + nom + " {\n"
                                "    background-color: white;\n"
                                "    color: " + texteBrun + ";\n"
                         "    border: 1px solid " + bordure + ";\n"
                       "    border-radius: 20px;\n"
                       "    padding-left: 15px;\n"
                       "    font-size: " + enTexte(tailleTexte) + "px;\n}";
}

string charte::styleFond(string nom, string zone) const
{
    string couleur = (zone == "sidebar") ? fondSidebar : fondPrincipal;
    return "QFrame#" + nom + " {\n"
                             "    background-color: " + couleur + ";\n"
                       "    border: none;\n}";
}

string charte::styleCarte(string nom) const
{
    return "QFrame#" + nom + " {\n"
                             "    background-color: #FDFBF9;\n"
                             "    border: 1px solid " + bordure + ";\n"
                       "    border-radius: " + enTexte(rayon) + "px;\n}";
}

string charte::styleBoutonSecondaire(string nom, bool aligneGauche) const
{
    string s = "QPushButton#" + nom + " {\n"
                                      "    background-color: white;\n"
                                      "    color: " + texteBrun + ";\n"
                             "    border: 1px solid " + bordure + ";\n"
                           "    border-radius: " + enTexte(rayon) + "px;\n"
                                  "    font-size: " + enTexte(tailleTexte) + "px;\n"
                                        "    font-weight: bold;\n";
    if (aligneGauche)
        s += "    text-align: left;\n    padding-left: 12px;\n";
    s += "}\nQPushButton#" + nom + ":hover { background-color: " + survol + "; }";
    if (aligneGauche)
        s += "\nQPushButton#" + nom + "::menu-indicator { right: 10px; }";
    return s;
}

string charte::styleBoutonPatient(string nom) const
{
    return "QPushButton#" + nom + " {\n"
                                  "    background-color: transparent;\n"
                                  "    color: " + texteBrun + ";\n"
                         "    border: none;\n"
                         "    border-radius: " + enTexte(rayon) + "px;\n"
                              "    text-align: left;\n"
                              "    padding-left: 55px;\n"
                              "    font-size: " + enTexte(tailleTexte) + "px;\n"
                                    "    font-weight: bold;\n}\n"
                                    "QPushButton#" + nom + ":hover { background-color: " + survol + "; }\n"
                                                            "QPushButton#" + nom + ":checked { background-color: " + survol + "; }";
}

string charte::styleAvatar(string nom, int diametre, bool accentue) const
{
    string s = "QLabel#" + nom + " {\n"
                                 "    background-color: " + (accentue ? accent : bordure) + ";\n";
    if (accentue)
        s += "    color: white;\n    font-weight: bold;\n";
    s += "    border-radius: " + enTexte(diametre / 2) + "px;\n}";
    return s;
}

string charte::styleZoneTexte(string nom) const
{
    return "QTextEdit#" + nom + " {\n"
                                "    background-color: #FDFBF9;\n"
                                "    border: 1px solid " + bordure + ";\n"
                       "    border-radius: " + enTexte(rayon) + "px;\n"
                              "    color: " + texteBrun + ";\n"
                         "    font-size: " + enTexte(taillePetit + 1) + "px;\n"
                                        "    padding: 6px;\n}";
}

string charte::styleSidebar(string nom) const
{
    return "QFrame#" + nom + " {\n"
                             "    background-color: " + fondSidebar + ";\n"
                           "    border: 2px solid " + accent + ";\n}";
}

string charte::styleChampDiscret(string nom, string type) const
{
    const int taille = (type == "nom") ? tailleTitre - 2 : tailleTexte + 2;
    return "QLineEdit#" + nom + " {\n"
                                "    background-color: transparent;\n"
                                "    color: " + texteBrun + ";\n"
                         "    border: none;\n"
                         "    border-bottom: 1px solid transparent;\n"
                         "    padding: 0px;\n"
                         "    font-size: " + enTexte(taille) + "px;\n"
                               "    font-weight: bold;\n}\n"
                               "QLineEdit#" + nom + ":hover { border-bottom: 1px dashed " + texteSecondaire + "; }\n"
                                                                             "QLineEdit#" + nom + ":focus { border-bottom: 1px solid " + accent + "; }";
}

string charte::styleMenu(string nom) const
{
    return "QMenu#" + nom + " {\n"
                            "    background-color: white;\n"
                            "    color: " + texteBrun + ";\n"
                         "    border: 1px solid " + bordure + ";\n"
                       "    border-radius: " + enTexte(rayon) + "px;\n"
                              "    padding: 4px;\n"
                              "    font-size: " + enTexte(tailleTexte) + "px;\n}\n"
                                    "QMenu#" + nom + "::item { padding: 6px 22px 6px 28px; border-radius: 6px; }\n"
                   "QMenu#" + nom + "::item:selected { background-color: " + survol + "; color: " + texteBrun + "; }\n"
                                                                                               "QMenu#" + nom + "::item:checked { font-weight: bold; }\n"
                   "QMenu#" + nom + "::indicator { left: 8px; width: 12px; height: 12px; }";
}

string charte::styleScrollListe(string nom) const
{
    return "QScrollArea#" + nom + " { background: transparent; border: none; }\n"
                                  "QScrollArea#" + nom + " QWidget#qt_scrollarea_viewport { background: transparent; }\n"
                   "QScrollArea#" + nom + " QWidget#patientsContainer { background: transparent; }\n"
                   "QScrollArea#" + nom + " QScrollBar:vertical { background: transparent; width: 8px; margin: 0; }\n"
                   "QScrollArea#" + nom + " QScrollBar::handle:vertical { background: " + bordure + "; border-radius: 4px; min-height: 24px; }\n"
                                                                             "QScrollArea#" + nom + " QScrollBar::add-line:vertical, QScrollArea#" + nom + " QScrollBar::sub-line:vertical { height: 0px; }\n"
                                                                          "QScrollArea#" + nom + " QScrollBar::add-page:vertical, QScrollArea#" + nom + " QScrollBar::sub-page:vertical { background: transparent; }";
}

void charte::afficher() const
{
    cout << "===== CHARTE GRAPHIQUE =====" << endl;
    cout << "Fond principal   : " << fondPrincipal << endl;
    cout << "Fond sidebar     : " << fondSidebar << endl;
    cout << "Texte principal  : " << texteBrun << endl;
    cout << "Texte secondaire : " << texteSecondaire << endl;
    cout << "Bordure          : " << bordure << endl;
    cout << "Survol           : " << survol << endl;
    cout << "Accent           : " << accent << endl;
    cout << "Police           : " << police << endl;
    cout << "Tailles (titre/texte/petit) : " << tailleTitre << "/"
         << tailleTexte << "/" << taillePetit << " px" << endl;
    cout << "Rayon des coins  : " << rayon << " px" << endl;
}




static QString qss(const std::string &s)
{
    return QString::fromStdString(s);
}

static const QString FORMAT_DATE  = QStringLiteral("dd/MM/yyyy");
static const QString FORMAT_HEURE = QStringLiteral("HH:mm");

// Raccourcit un texte pour qu'il tienne dans une ligne de la liste des patients
static QString elide(const QString &texte, int largeur)
{
    QFont f;
    f.setPixelSize(12);
    f.setBold(true);
    return QFontMetrics(f).elidedText(texte, Qt::ElideRight, largeur);
}

// Critere de tri : "a est-il avant b ?"
static bool avant(const Patient &a, const Patient &b, int critere)
{
    auto parHeure = [](const Patient &x, const Patient &y) {
        return QDateTime(x.date, x.heure) < QDateTime(y.date, y.heure);
    };
    auto rang = [](const Patient &p) {          // alerte < neutre < succes
        return p.statutType == "alerte" ? 0 : (p.statutType == "neutre" ? 1 : 2);
    };

    switch (critere) {
    case 0:  return parHeure(a, b);
    case 1:  return parHeure(b, a);
    case 2:  return QString::localeAwareCompare(a.nom, b.nom) < 0;
    case 3:  return QString::localeAwareCompare(b.nom, a.nom) < 0;
    case 4:  return QString::localeAwareCompare(a.motif, b.motif) < 0;
    case 5:  if (rang(a) != rang(b)) return rang(a) < rang(b);
        return parHeure(a, b);
    default: return a.id < b.id;
    }
}

GestionRendezvous::GestionRendezvous(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionRendezvous)
{
    ui->setupUi(this);

    ui->btnConsultations->setParent(ui->sideBar);
    ui->btnConsultations->setMinimumSize(210, 45);
    ui->btnConsultations->setGeometry(15, 250, 210, 45);
    ui->btnConsultations->show();
    ui->searchBar->setParent(ui->mainContent);
    ui->searchBar->setGeometry(20, 95, 420, 40);
    ui->searchBar->setPlaceholderText(QString::fromUtf8("Rechercher..."));
    ui->searchBar->show();
    ui->btnTrier->setGeometry(450, 95, 130, 40);
    ui->pageTitle->setGeometry(20, 15, 350, 30);
    ui->pageSubtitle->setGeometry(20, 45, 350, 18);
    ui->patientsFrame->move(20, 135);
    ui->selectedPatientFrame->move(340, 135);
    ui->appointmentStatsFrame->setGeometry(20, 610, 1020, 130);
    m_graphiqueRendezVous = new AppointmentChart(ui->appointmentStatsFrame);
    m_graphiqueRendezVous->setGeometry(18, 44, 984, 78);
    m_graphiqueRendezVous->show();

    m_listeLayout = new QVBoxLayout(ui->patientsContainer);
    m_listeLayout->setContentsMargins(10, 5, 6, 5);
    m_listeLayout->setSpacing(10);
    m_groupe = new QButtonGroup(this);
    m_groupe->setExclusive(true);

    chargerLogo();
    appliquerCharte();
    configurerChamps();
    configurerTri();

    connect(ui->btnNouveauPatient, &QPushButton::clicked, this, &GestionRendezvous::nouveauPatient);
    connect(ui->btnEnregistrer, &QPushButton::clicked,
            this, &GestionRendezvous::enregistrerPatient);
    connect(ui->btnExporterPreConsultation, &QPushButton::clicked,
            this, &GestionRendezvous::exporterPreConsultationPdf);

    ajouterPatient(QString::fromUtf8("Milo"), QDate::currentDate(), QTime(9, 0));
    reconstruireListe();
    selectionnerPatient(m_patients.first().id);
}

GestionRendezvous::~GestionRendezvous()
{
    delete ui;
}


void GestionRendezvous::chargerLogo()
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QString cwd    = QDir::currentPath();

    QStringList candidats = {
        ":/images/pawche.jpeg",            
        ":/pawche.jpeg",
        appDir + "/pawche.jpeg",           
        appDir + "/images/pawche.jpeg",
        cwd + "/pawche.jpeg",
        cwd + "/images/pawche.jpeg",
        "../../../Downloads/pawche.jpeg"   
    };
    const QStringList dl = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
    for (const QString &d : dl)
        candidats << d + "/pawche.jpeg";

    QPixmap pm;
    for (const QString &c : qAsConst(candidats)) {
        if (QFile::exists(c) && pm.load(c)) {
            qInfo() << "Logo charge depuis" << c;
            break;
        }
    }

    QLabel *logo = ui->logoLabel;
    logo->setAlignment(Qt::AlignCenter);
    logo->setScaledContents(false);

    if (!pm.isNull()) {
        const qreal dpr = devicePixelRatioF();
        QPixmap p = pm.scaled(logo->size() * dpr, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        p.setDevicePixelRatio(dpr);
        logo->setPixmap(p);
    } else {
        qWarning() << "Logo introuvable. Chemins essayes :" << candidats;
        logo->setText(QString::fromUtf8("🐾  Pawche"));
        logo->setStyleSheet(qss(m_charte.styleLabel("logoLabel", "titre")));
    }
}

void GestionRendezvous::appliquer(const QString &nom, const std::string &style)
{
    if (QWidget *w = findChild<QWidget *>(nom))
        w->setStyleSheet(qss(style));
}

void GestionRendezvous::appliquerCharte()
{
    const charte &c = m_charte;

    if (QMenuBar *mb = findChild<QMenuBar *>())    mb->hide();
    if (QStatusBar *sb = findChild<QStatusBar *>()) sb->hide();

    appliquer("centralFrame", c.styleFond("centralFrame", "principal"));
    appliquer("sideBar",      c.styleSidebar("sideBar"));      // cadre exterieur visible
    appliquer("mainContent",  c.styleFond("mainContent", "sidebar"));

    for (const char *n : {"btnAnimaux", "btnClients", "btnConsultations",
                          "btnProduits", "btnCaisse"})
        appliquer(n, c.styleBoutonMenu(n));

    appliquer("searchBar",         c.styleChampTexte("searchBar"));
    appliquer("btnCabinet",        c.styleBoutonSecondaire("btnCabinet"));
    appliquer("btnNouveauPatient", c.styleBoutonPrincipal("btnNouveauPatient"));
    appliquer("notifLabel",        c.styleLabel("notifLabel", "valeur"));
    appliquer("avatarLabel",       c.styleAvatar("avatarLabel", 40, true));
    appliquer("posteLabel",        c.styleLabel("posteLabel", "etiquette"));
    appliquer("posteBadge",        c.styleStatut("posteBadge", "neutre"));
    appliquer("salleLabel",        c.styleLabel("salleLabel", "sous-titre"));

    appliquer("pageTitle",    c.styleLabel("pageTitle", "titre"));
    appliquer("pageSubtitle", c.styleLabel("pageSubtitle", "sous-titre"));

    // ----- Liste des patients du jour -----
    appliquer("patientsFrame",      c.styleCadre("patientsFrame", "white"));
    appliquer("patientsTitle",      c.styleLabel("patientsTitle", "rubrique"));
    appliquer("patientsCountBadge", c.styleLabel("patientsCountBadge", "petit"));
    appliquer("patientsScroll",     c.styleScrollListe("patientsScroll"));
    appliquer("appointmentStatsFrame", c.styleCadre("appointmentStatsFrame", "white"));

    appliquer("selectedPatientFrame", c.styleCadre("selectedPatientFrame", "white"));
    appliquer("btnEnregistrer", c.styleBoutonPrincipal("btnEnregistrer"));
    appliquer("btnExporterPreConsultation",
              c.styleBoutonSecondaire("btnExporterPreConsultation"));
    appliquer("btnTrier",        c.styleBoutonSecondaire("btnTrier", true));
    appliquer("avatarSelected",  c.styleAvatar("avatarSelected", 60));
    appliquer("patientName",     c.styleChampDiscret("patientName", "nom"));   // editable
    appliquer("patientBreedAge", c.styleLabel("patientBreedAge", "sous-titre"));
    appliquer("ownerLabel",      c.styleLabel("ownerLabel", "texte"));
    appliquer("dossierLabel",    c.styleLabel("dossierLabel", "sous-titre"));
    appliquer("genderLabel",     c.styleLabel("genderLabel", "accent"));

    for (const char *k : {"date", "heure", "nom", "tel", "motif", "notes"}) {
        const std::string key = k;
        const std::string champ = std::string("champ") + char(std::toupper(k[0])) + (k + 1);
        appliquer(QString::fromStdString(key + "Card"),    c.styleCarte(key + "Card"));
        appliquer(QString::fromStdString(key + "Caption"), c.styleLabel(key + "Caption", "etiquette"));
        appliquer(QString::fromStdString(champ),           c.styleChampDiscret(champ, "valeur"));
    }

    // zones de saisie
    for (const char *n : {"motifTitle", "diagnosticTitle", "actesTitle"})
        appliquer(n, c.styleLabel(n, "section"));
    for (const char *n : {"motifText", "diagnosticText"})
        appliquer(n, c.styleZoneTexte(n));
    appliquer("actesSubtitle", c.styleLabel("actesSubtitle", "petit"));
}

void GestionRendezvous::configurerChamps()
{
    ui->champDate->setInputMask("00/00/0000;_");
    ui->champHeure->setInputMask("00:00;_");
    ui->champTel->setValidator(
        new QRegularExpressionValidator(QRegularExpression("[0-9 +().\\-/]*"), this));
    appliquerModeEdition(false);

    connect(ui->patientName, &QLineEdit::textEdited, this, [this](const QString &t) {
        if (!m_modeEdition) return;
        if (Patient *p = patientCourant()) {
            p->nom = t;
            ui->champNom->setText(t);
            majLigne(p->id);
        }
    });
    connect(ui->champNom, &QLineEdit::textEdited, this, [this](const QString &t) {
        if (!m_modeEdition) return;
        if (Patient *p = patientCourant()) {
            p->nom = t;
            ui->patientName->setText(t);
            majLigne(p->id);
        }
    });

    connect(ui->champMotif, &QLineEdit::textEdited, this, [this](const QString &t) {
        if (!m_modeEdition) return;
        if (Patient *p = patientCourant()) { p->motif = t; majLigne(p->id); }
    });
    connect(ui->champTel, &QLineEdit::textEdited, this, [this](const QString &t) {
        if (!m_modeEdition) return;
        if (Patient *p = patientCourant()) p->telephone = t;
    });
    connect(ui->champNotes, &QLineEdit::textEdited, this, [this](const QString &t) {
        if (!m_modeEdition) return;
        if (Patient *p = patientCourant()) p->notes = t;
    });

    connect(ui->champDate, &QLineEdit::editingFinished, this, [this]() {
        Patient *p = patientCourant();
        if (!p || !m_modeEdition) return;
        const QDate d = QDate::fromString(ui->champDate->text(), FORMAT_DATE);
        if (d.isValid()) p->date = d;
        else ui->champDate->setText(p->date.toString(FORMAT_DATE));
        majLigne(p->id);
    });
    connect(ui->champHeure, &QLineEdit::editingFinished, this, [this]() {
        Patient *p = patientCourant();
        if (!p || !m_modeEdition) return;
        const QTime t = QTime::fromString(ui->champHeure->text(), FORMAT_HEURE);
        if (t.isValid()) p->heure = t;
        else ui->champHeure->setText(p->heure.toString(FORMAT_HEURE));
        majLigne(p->id);
    });

    connect(ui->motifText, &QTextEdit::textChanged, this, [this]() {
        if (m_chargement || !m_modeEdition) return;
        if (Patient *p = patientCourant()) p->constatations = ui->motifText->toPlainText();
    });
    connect(ui->diagnosticText, &QTextEdit::textChanged, this, [this]() {
        if (m_chargement || !m_modeEdition) return;
        if (Patient *p = patientCourant()) p->diagnostic = ui->diagnosticText->toPlainText();
    });
}

// bouton Trier
void GestionRendezvous::configurerTri()
{
    struct Option { const char *texte; int critere; };
    const Option options[] = {
                               { "Heure — plus tôt d'abord",   HeureCroissante },
                               { "Heure — plus tard d'abord",  HeureDecroissante },
                               { "Nom — A → Z",                NomAZ },
                               { "Nom — Z → A",                NomZA },
                               { "Motif — A → Z",              MotifAZ },
                               { "Statut — urgents d'abord",   StatutUrgentsDabord },
                               { "N° de dossier",              NumeroDossier },
                               };

    QMenu *menu = new QMenu(ui->btnTrier);
    menu->setObjectName("menuTri");
    menu->setStyleSheet(qss(m_charte.styleMenu("menuTri")));

    QActionGroup *groupe = new QActionGroup(menu);
    groupe->setExclusive(true);
    for (const Option &o : options) {
        QAction *a = menu->addAction(QString::fromUtf8(o.texte));
        a->setCheckable(true);
        a->setActionGroup(groupe);
        a->setChecked(o.critere == m_critereTri);
        const int critere = o.critere;
        connect(a, &QAction::triggered, this, [this, critere]() { appliquerTri(critere); });
    }
    ui->btnTrier->setMenu(menu);
}

void GestionRendezvous::appliquerTri(int critere)
{
    m_critereTri = critere;
    reconstruireListe();
}

// patients
QString GestionRendezvous::genererDossier()
{
    
    return QString("DOS-%1-%2").arg(QDate::currentDate().year())
        .arg(m_dernierId, 4, 10, QChar('0'));
}

int GestionRendezvous::ajouterPatient(const QString &nom, const QDate &date, const QTime &heure)
{
    Patient p;
    p.id      = ++m_dernierId;
    p.dossier = genererDossier();
    p.nom     = nom;
    p.date    = date;
    p.heure   = heure;
    m_patients.append(p);
    return p.id;
}

Patient *GestionRendezvous::trouver(int id)
{
    for (Patient &p : m_patients)
        if (p.id == id) return &p;
    return nullptr;
}

Patient *GestionRendezvous::patientCourant()
{
    return trouver(m_courant);
}


void GestionRendezvous::nouveauPatient()
{
    const QTime maintenant = QTime::currentTime();
    const int id = ajouterPatient(QString::fromUtf8("Nouveau patient"), QDate::currentDate(),
                                  QTime(maintenant.hour(), maintenant.minute()));
    m_courant = id;
    reconstruireListe();
    selectionnerPatient(id);
    appliquerModeEdition(true);

    // faire defiler jusqu'a la nouvelle ligne une fois la liste mise en page
    QTimer::singleShot(0, this, [this, id]() {
        if (QPushButton *b = findChild<QPushButton *>(QString("btnPatient%1").arg(id)))
            ui->patientsScroll->ensureWidgetVisible(b);
    });

    ui->patientName->setFocus();
    ui->patientName->selectAll();
}

void GestionRendezvous::selectionnerPatient(int id)
{
    Patient *p = trouver(id);
    if (!p) return;
    appliquerModeEdition(false);
    m_courant = id;
    if (QPushButton *b = findChild<QPushButton *>(QString("btnPatient%1").arg(id)))
        b->setChecked(true);
    afficherPatient(*p);
}

void GestionRendezvous::afficherPatient(const Patient &p)
{
    m_chargement = true;
    ui->patientName->setText(p.nom);
    ui->champNom->setText(p.nom);
    ui->champDate->setText(p.date.toString(FORMAT_DATE));
    ui->champHeure->setText(p.heure.toString(FORMAT_HEURE));
    ui->champMotif->setText(p.motif);
    ui->champTel->setText(p.telephone);
    ui->champNotes->setText(p.notes);
    ui->motifText->setPlainText(p.constatations);
    ui->diagnosticText->setPlainText(p.diagnostic);
    ui->dossierLabel->setText(QString("Dossier #%1").arg(p.dossier));
    m_chargement = false;
}

void GestionRendezvous::appliquerModeEdition(bool actif)
{
    m_modeEdition = actif;
    ui->patientName->setReadOnly(!actif);
    ui->champNom->setReadOnly(!actif);
    ui->champDate->setReadOnly(!actif);
    ui->champHeure->setReadOnly(!actif);
    ui->champMotif->setReadOnly(!actif);
    ui->champTel->setReadOnly(!actif);
    ui->champNotes->setReadOnly(!actif);
    ui->motifText->setReadOnly(!actif);
    ui->diagnosticText->setReadOnly(!actif);
    ui->btnEnregistrer->setEnabled(actif);
    ui->btnEnregistrer->setText(actif
        ? QString::fromUtf8("Enregistrer")
        : QString::fromUtf8("Enregistré"));
}

//  liste des patients
void GestionRendezvous::reconstruireListe()
{
    // 1. vider la liste
    while (QLayoutItem *it = m_listeLayout->takeAt(0)) {
        if (QWidget *w = it->widget()) {
            if (auto *b = qobject_cast<QAbstractButton *>(w))
                m_groupe->removeButton(b);
            w->hide();
            w->setParent(nullptr);
            w->deleteLater();
        }
        delete it;
    }

    //  ordre d'affichage selon le critere de tri
    QVector<int> ordre;
    for (const Patient &p : qAsConst(m_patients))
        ordre.append(p.id);
    std::stable_sort(ordre.begin(), ordre.end(), [this](int a, int b) {
        return avant(*trouver(a), *trouver(b), m_critereTri);
    });

    // une ligne par patient : bouton + avatar + badge de statut
    for (int id : qAsConst(ordre)) {
        const QString nBtn = QString("btnPatient%1").arg(id);
        const QString nAv  = QString("avatarPatient%1").arg(id);
        const QString nSt  = QString("statusPatient%1").arg(id);

        auto *b = new QPushButton(ui->patientsContainer);
        b->setObjectName(nBtn);
        b->setCursor(Qt::PointingHandCursor);
        b->setCheckable(true);
        b->setFixedSize(262, 60);
        b->setContextMenuPolicy(Qt::CustomContextMenu);
        b->setStyleSheet(qss(m_charte.styleBoutonPatient(nBtn.toStdString())));
        m_groupe->addButton(b);
        connect(b, &QPushButton::clicked, this, [this, id]() { selectionnerPatient(id); });
        connect(b, &QPushButton::customContextMenuRequested, this,
                [this, b, id](const QPoint &pos) {
            QMenu menu(b);
            QAction *modifier = menu.addAction(QString::fromUtf8("Modifier le patient"));
            QAction *supprimer = menu.addAction(QString::fromUtf8("Supprimer le patient"));
            QAction *choix = menu.exec(b->mapToGlobal(pos));
            if (choix == modifier)
                modifierPatient(id);
            else if (choix == supprimer)
                supprimerPatient(id);
        });

        auto *av = new QLabel(QString::fromUtf8("🐾"), b);
        av->setObjectName(nAv);
        av->setGeometry(10, 12, 36, 36);
        av->setAlignment(Qt::AlignCenter);
        av->setAttribute(Qt::WA_TransparentForMouseEvents);
        av->setStyleSheet(qss(m_charte.styleAvatar(nAv.toStdString(), 36)));

        auto *st = new QLabel(b);
        st->setObjectName(nSt);
        st->setGeometry(184, 20, 68, 20);
        st->setAlignment(Qt::AlignCenter);
        st->setAttribute(Qt::WA_TransparentForMouseEvents);

        m_listeLayout->addWidget(b);
        b->show();
        av->show();
        st->show();

        b->setChecked(id == m_courant);
        majLigne(id);
    }
    m_listeLayout->addStretch(1);
    majCompteur();
}

void GestionRendezvous::majLigne(int id)
{
    const Patient *p = trouver(id);
    auto *b = findChild<QPushButton *>(QString("btnPatient%1").arg(id));
    if (!p || !b) return;

    const QString nom   = p->nom.trimmed().isEmpty() ? QString::fromUtf8("(sans nom)") : p->nom;
    const QString ligne2 = QString("%1 • %2").arg(p->heure.toString(FORMAT_HEURE),
                                                  p->motif.trimmed().isEmpty() ? QString::fromUtf8("—") : p->motif);
    b->setText(elide(nom, 125) + "\n" + elide(ligne2, 125));

    if (auto *st = findChild<QLabel *>(QString("statusPatient%1").arg(id))) {
        st->setText(p->statut);
        st->setStyleSheet(qss(m_charte.styleStatut(st->objectName().toStdString(),
                                                   p->statutType.toStdString())));
    }
}

void GestionRendezvous::majCompteur()
{
    int n = 0;
    for (const Patient &p : qAsConst(m_patients))
        if (p.statut == "En attente") ++n;
    ui->patientsCountBadge->setText(QString("%1 en attente").arg(n));
    majStatistiques();
}

void GestionRendezvous::majStatistiques()
{
    int realises = 0;
    for (const Patient &p : qAsConst(m_patients))
        if (p.rendezVousRealise) ++realises;

    const int total = m_patients.size();
    ui->statTotalLabel->setText(QString::fromUtf8("Total des rendez-vous : %1").arg(total));
    ui->statRealisesLabel->setText(QString::fromUtf8("Réalisés : %1").arg(realises));
    ui->statARealiserLabel->setText(QString::fromUtf8("À réaliser : %1").arg(total - realises));
    m_graphiqueRendezVous->setAppointments(m_patients);
}

void GestionRendezvous::modifierPatient(int id)
{
    if (!trouver(id))
        return;
    selectionnerPatient(id);
    appliquerModeEdition(true);
    ui->patientName->setFocus();
    ui->patientName->selectAll();
}

void GestionRendezvous::enregistrerPatient()
{
    Patient *patient = patientCourant();
    if (!patient || !m_modeEdition)
        return;

    const QDate date = QDate::fromString(ui->champDate->text(), FORMAT_DATE);
    if (!date.isValid()) {
        QMessageBox::warning(this, QString::fromUtf8("Date invalide"),
                             QString::fromUtf8("Saisissez une date valide avant d'enregistrer."));
        ui->champDate->setFocus();
        return;
    }

    const QTime heure = QTime::fromString(ui->champHeure->text(), FORMAT_HEURE);
    if (!heure.isValid()) {
        QMessageBox::warning(this, QString::fromUtf8("Heure invalide"),
                             QString::fromUtf8("Saisissez une heure valide avant d'enregistrer."));
        ui->champHeure->setFocus();
        return;
    }

    patient->date = date;
    patient->heure = heure;
    majLigne(patient->id);
    majCompteur();
    appliquerModeEdition(false);
}

void GestionRendezvous::exporterPreConsultationPdf()
{
    const Patient *patient = patientCourant();
    if (!patient) {
        QMessageBox::warning(this, QString::fromUtf8("Aucun patient"),
                             QString::fromUtf8("Sélectionnez un patient avant l'export."));
        return;
    }

    const QString nom = patient->nom.trimmed().isEmpty()
        ? QString::fromUtf8("patient")
        : patient->nom.trimmed();
    const QString fichierParDefaut =
        QString("preconsultation_%1.pdf").arg(patient->dossier);
    const QString chemin = QFileDialog::getSaveFileName(
        this, QString::fromUtf8("Exporter la pré-consultation"),
        QDir::home().filePath(fichierParDefaut),
        QString::fromUtf8("Fichier PDF (*.pdf)"));
    if (chemin.isEmpty())
        return;

    QString cheminPdf = chemin;
    if (!cheminPdf.endsWith(".pdf", Qt::CaseInsensitive))
        cheminPdf += ".pdf";

    QSaveFile fichierPdf(cheminPdf);
    if (!fichierPdf.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, QString::fromUtf8("Échec de l'export"),
                              QString::fromUtf8("Impossible de créer le fichier PDF : %1")
                                  .arg(fichierPdf.errorString()));
        return;
    }

    auto html = [](const QString &value) {
        const QString safeValue = value.trimmed().isEmpty()
            ? QString::fromUtf8("Non renseigné")
            : value.trimmed();
        return safeValue.toHtmlEscaped().replace("\n", "<br>");
    };

    QTextDocument document;
    document.setHtml(QString::fromUtf8(
        "<html><head><meta charset='utf-8'/>"
        "<style>"
        "body{font-family:Arial,sans-serif;color:#3f302a;font-size:11pt;}"
        "h1{color:#6B3F2E;font-size:20pt;}"
        "h2{color:#6B3F2E;font-size:13pt;border-bottom:1px solid #F3E6DC;"
        "padding-bottom:5px;margin-top:22px;}"
        ".meta{color:#A98268;font-size:10pt;}"
        ".field{margin:12px 0;}"
        ".label{font-weight:bold;color:#6B3F2E;}"
        ".value{margin-top:4px;padding:8px;background:#FDFBF9;"
        "border:1px solid #F3E6DC;}"
        "</style></head><body>"
        "<h1>Questionnaire de pré-consultation</h1>"
        "<p class='meta'>Dossier : %1 &nbsp; | &nbsp; Exporté le : %2</p>"
        "<h2>Informations du patient</h2>"
        "<div class='field'><div class='label'>Nom de l'animal</div>"
        "<div class='value'>%3</div></div>"
        "<div class='field'><div class='label'>Date et heure du rendez-vous</div>"
        "<div class='value'>%4 à %5</div></div>"
        "<div class='field'><div class='label'>Téléphone du propriétaire</div>"
        "<div class='value'>%6</div></div>"
        "<h2>Pré-consultation</h2>"
        "<div class='field'><div class='label'>Motif de la consultation</div>"
        "<div class='value'>%7</div></div>"
        "<div class='field'><div class='label'>Notes communiquées</div>"
        "<div class='value'>%8</div></div>"
        "<div class='field'><div class='label'>Constatations préalables</div>"
        "<div class='value'>%9</div></div>"
        "</body></html>")
        .arg(html(patient->dossier),
             html(QDate::currentDate().toString(FORMAT_DATE)),
             html(nom),
             html(patient->date.toString(FORMAT_DATE)),
             html(patient->heure.toString(FORMAT_HEURE)),
             html(patient->telephone),
             html(patient->motif),
             html(patient->notes),
             html(patient->constatations)));
    document.setDocumentMargin(48);
    {
        QPdfWriter writer(&fichierPdf);
        writer.setPageSize(QPageSize(QPageSize::A4));
        writer.setResolution(96);
        document.print(&writer);
    }
    if (!fichierPdf.commit()) {
        QMessageBox::critical(this, QString::fromUtf8("Échec de l'export"),
                              QString::fromUtf8("Impossible d'enregistrer le PDF : %1")
                                  .arg(fichierPdf.errorString()));
        return;
    }

    QMessageBox::information(this, QString::fromUtf8("Export terminé"),
                             QString::fromUtf8("Le questionnaire de pré-consultation a été enregistré."));
}

void GestionRendezvous::supprimerPatient(int id)
{
    Patient *patient = trouver(id);
    if (!patient)
        return;

    const QString nom = patient->nom.trimmed().isEmpty()
        ? QString::fromUtf8("ce patient")
        : patient->nom;
    const auto confirmation = QMessageBox::question(
        this, QString::fromUtf8("Supprimer le patient"),
        QString::fromUtf8("Voulez-vous vraiment supprimer %1 ?").arg(nom),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (confirmation != QMessageBox::Yes)
        return;

    const int index = int(patient - m_patients.data());
    m_patients.removeAt(index);
    if (m_courant == id)
        m_courant = -1;

    reconstruireListe();
    if (!m_patients.isEmpty()) {
        selectionnerPatient(m_patients.first().id);
        return;
    }

    ui->patientName->clear();
    ui->champNom->clear();
    ui->champDate->clear();
    ui->champHeure->clear();
    ui->champMotif->clear();
    ui->champTel->clear();
    ui->champNotes->clear();
    ui->motifText->clear();
    ui->diagnosticText->clear();
    ui->dossierLabel->setText(QString::fromUtf8("Aucun dossier sélectionné"));
    appliquerModeEdition(false);
}

void GestionRendezvous::setStatutPatient(int numero, const QString &texte, const QString &type)
{
    Patient *p = trouver(numero);
    if (!p)
        return;
    p->statut     = texte;
    p->statutType = type;
    p->rendezVousRealise =
        type == "succes"
        || texte.compare(QString::fromUtf8("Réalisé"), Qt::CaseInsensitive) == 0
        || texte.compare(QStringLiteral("Realise"), Qt::CaseInsensitive) == 0
        || texte.compare(QString::fromUtf8("Terminé"), Qt::CaseInsensitive) == 0
        || texte.compare(QStringLiteral("Termine"), Qt::CaseInsensitive) == 0;
    majLigne(numero);
    majCompteur();
}