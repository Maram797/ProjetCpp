#include "gestionrendezvous.h"
#include "ui_gestionrendezvous.h"

#include <QActionGroup>
#include <QPdfWriter>
#include <QSaveFile>
#include <QtSql>
#include <QtWidgets>
#include <algorithm>
#include <functional>

class AppointmentChart : public QWidget
{
public:
    explicit AppointmentChart(QWidget *parent = nullptr) : QWidget(parent) { setAttribute(Qt::WA_TransparentForMouseEvents); }
    void setAppointments(const QVector<Patient> &patients)
    {
        QMap<QDate, QPair<int, int>> days;
        for (const Patient &p : patients) { ++days[p.date].first; if (p.rendezVousRealise) ++days[p.date].second; }
        m_dates = days.keys().toVector(); m_done.clear(); m_maxTotal = 0;
        for (const QDate &date : m_dates) { m_maxTotal = qMax(m_maxTotal, days[date].first); m_done << days[date].second; }
        update();
    }
protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this); const QRectF plot(42, 12, width() - 58, height() - 30);
        p.setRenderHint(QPainter::Antialiasing); p.setPen(QColor("#6B3F2E"));
        p.drawLine(plot.bottomLeft(), plot.topLeft()); p.drawLine(plot.bottomLeft(), plot.bottomRight());
        if (m_dates.isEmpty()) return;
        const int maximum = qMax(1, m_maxTotal);
        QVector<QPointF> points;
        for (int i = 0; i < m_dates.size(); ++i) {
            const qreal x = m_dates.size() == 1 ? plot.center().x() : plot.left() + plot.width() * i / (m_dates.size() - 1);
            points << QPointF(x, plot.bottom() - plot.height() * m_done[i] / maximum);
        }
        p.setPen(QPen(QColor("#E77C8D"), 2)); p.drawPolyline(points.constData(), points.size());
        p.setBrush(QColor("#E77C8D"));
        for (const QPointF &point : points) p.drawEllipse(point, 2.5, 2.5);
        p.setPen(QColor("#A98268")); const int step = qMax(1, m_dates.size() / 6);
        for (int i = 0; i < m_dates.size(); i += step)
            p.drawText(QRectF(points[i].x() - 25, plot.bottom() + 2, 50, 12), Qt::AlignHCenter, m_dates[i].toString("dd/MM"));
    }
private:
    QVector<QDate> m_dates;
    QVector<int> m_done;
    int m_maxTotal = 0;
};


static const QString FORMAT_DATE = QStringLiteral("dd/MM/yyyy"), FORMAT_HEURE = QStringLiteral("HH:mm"),
    SQL_FORMAT_HEURE = QStringLiteral("YYYY-MM-DD HH24:MI:SS.FF6"), SQL_FORMAT_DATE = QStringLiteral("YYYY-MM-DD");

static QString U(const char *s) { return QString::fromUtf8(s); }
static QString numeroDossier(qint64 id) { return QString("DOS-%1-%2").arg(QDate::currentDate().year()).arg(id, 4, 10, QChar('0')); }

static QString statusStyle(const QString &type)
{
    const bool success = type == "succes", alert = type == "alerte";
    return QString("QLabel { background: %1; color: %2; border-radius: 10px; font-weight: bold; }")
        .arg(success ? "#DDF3E4" : alert ? "#FCE1E5" : "#F3E6DC", success ? "#2E7D46" : alert ? "#C0394C" : "#6B3F2E");
}

static QString elide(const QString &texte, int largeur)
{
    QFont f; f.setPixelSize(12); f.setBold(true);
    return QFontMetrics(f).elidedText(texte, Qt::ElideRight, largeur);
}

static bool estRealise(const QString &texte)
{
    const QString s = texte.toLower();
    return s.contains("réalis") || s.contains("realis") || s.contains("terminé") || s.contains("termine");
}


static void echec(QWidget *parent, const char *titre, const char *message, const QString &detail)
{
    QMessageBox::critical(parent, U(titre), U(message).arg(detail));
}

template<class T>
static bool validerChamp(QWidget *parent, QLineEdit *champ, const QString &format, const char *titre, const char *message, T &valeur)
{
    valeur = T::fromString(champ->text(), format);
    if (valeur.isValid()) return true;
    QMessageBox::warning(parent, U(titre), U(message)); champ->setFocus();
    return false;
}

static bool avant(const Patient &a, const Patient &b, int critere)
{
    if (critere == 2 || critere == 3) {
        const int c = QString::localeAwareCompare(a.motif, b.motif);
        return critere == 2 ? c < 0 : c > 0;
    }
    return critere == 1 ? QDateTime(b.date, b.heure) < QDateTime(a.date, a.heure)
                        : QDateTime(a.date, a.heure) < QDateTime(b.date, b.heure);
}


GestionRendezvous::GestionRendezvous(QWidget *parent) : QMainWindow(parent), ui(new Ui::GestionRendezvous)
{
    ui->setupUi(this);

    ui->btnConsultations->setParent(ui->sideBar);
    ui->btnConsultations->setMinimumSize(210, 45); ui->btnConsultations->setGeometry(15, 250, 210, 45);
    ui->btnConsultations->show();
    ui->searchBar->setParent(ui->mainContent);
    ui->searchBar->setGeometry(20, 95, 420, 40); ui->searchBar->setPlaceholderText(U("Rechercher par motif..."));
    ui->searchBar->show();
    ui->btnTrier->setGeometry(450, 95, 130, 40); ui->pageTitle->setGeometry(20, 15, 350, 30);
    ui->pageSubtitle->setGeometry(20, 45, 350, 18); ui->patientsFrame->move(20, 135);
    ui->selectedPatientFrame->move(340, 135);
    ui->appointmentStatsFrame->setGeometry(20, 610, 1020, 130);
    m_graphiqueRendezVous = new AppointmentChart(ui->appointmentStatsFrame);
    m_graphiqueRendezVous->setGeometry(18, 44, 984, 78); m_graphiqueRendezVous->show();

    m_patientsContainer = new QWidget(ui->patientsFrame);
    m_patientsContainer->setGeometry(6, 60, 288, 330);
    m_patientsContainer->setAutoFillBackground(true); m_patientsContainer->setStyleSheet("background-color: white;");
    m_listeLayout = new QVBoxLayout(m_patientsContainer);
    m_listeLayout->setContentsMargins(10, 5, 6, 5); m_listeLayout->setSpacing(10);

    
    struct Action { QString texte; std::function<void()> fonction; };
    const Action actions[] = {
        {U("Modifier la fiche"), [this]() { modifierPatient(m_courant); }},
        {U("En attente"), [this]() { setStatutPatient(m_courant, U("En attente"), "neutre"); }},
        {U("Réalisé"), [this]() { setStatutPatient(m_courant, U("Réalisé"), "succes"); }}};
    const QString actionStyle = QStringLiteral(
        "QPushButton { background: #F3E6DC; color: #6B3F2E; border: none; border-radius: 6px; font-size: 10px; font-weight: bold; } "
        "QPushButton:disabled { background: #F5F5F5; color: #A0A0A0; }");
    auto *actionsWidget = new QWidget(ui->patientsFrame);
    actionsWidget->setGeometry(2, 405, 296, 46);
    auto *actionsLayout = new QHBoxLayout(actionsWidget);
    actionsLayout->setContentsMargins(8, 0, 8, 0); actionsLayout->setSpacing(4);
    for (const Action &a : actions) {
        auto *bouton = new QPushButton(a.texte, actionsWidget);
        bouton->setFixedHeight(36); bouton->setCursor(Qt::PointingHandCursor);
        bouton->setStyleSheet(actionStyle); bouton->setEnabled(false);
        actionsLayout->addWidget(bouton); m_actions << bouton;
        connect(bouton, &QPushButton::clicked, this, a.fonction);
    }

    m_groupe = new QButtonGroup(this);
    chargerLogo(); menuBar()->hide(); statusBar()->hide();
    configurerChamps(); configurerTri();
    connect(ui->searchBar, &QLineEdit::textChanged, this, [this](const QString &text) {
        m_rechercheMotif = text.trimmed(); reconstruireListe();
    });
    connect(ui->btnNouveauPatient, &QPushButton::clicked, this, &GestionRendezvous::nouveauPatient);
    connect(ui->btnEnregistrer, &QPushButton::clicked, this, &GestionRendezvous::enregistrerPatient);
    connect(ui->btnExporterPreConsultation, &QPushButton::clicked, this, &GestionRendezvous::exporterPreConsultationPdf);

    chargerDepuisBase();
    reconstruireListe();
    if (!m_patients.isEmpty()) selectionnerPatient(m_patients.first().id);
    else {
        afficherPatient(Patient());
        ui->dossierLabel->setText(U("Aucun dossier sélectionné"));
        for (QPushButton *bouton : m_actions) bouton->setEnabled(false);
    }
}

GestionRendezvous::~GestionRendezvous() { delete ui; }

void GestionRendezvous::chargerLogo()
{
    QPixmap image;
    for (const QString &chemin : {QString(":/images/pawche.jpeg"), QCoreApplication::applicationDirPath() + "/images/pawche.jpeg",
                                  QDir::currentPath() + "/images/pawche.jpeg"})
        if (image.load(chemin)) break;
    ui->logoLabel->setAlignment(Qt::AlignCenter);
    if (image.isNull()) ui->logoLabel->setText(U("🐾  Pawche"));
    else ui->logoLabel->setPixmap(image.scaled(ui->logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void GestionRendezvous::configurerChamps()
{
    ui->champDate->setInputMask("00/00/0000;_"); ui->champHeure->setInputMask("00:00;_");
    ui->champTel->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9 +().\\-/]*"), this));
    appliquerModeEdition(false);

    
    auto lier = [this](QLineEdit *champ, QString Patient::*membre, QLineEdit *miroir = nullptr) {
        connect(champ, &QLineEdit::textEdited, this, [this, membre, miroir](const QString &texte) {
            Patient *p = patientCourant();
            if (!m_modeEdition || !p) return;
            p->*membre = texte;
            if (miroir) miroir->setText(texte);
            majLigne(p->id);
        });
    };
    lier(ui->patientName, &Patient::nom, ui->champNom); lier(ui->champNom, &Patient::nom, ui->patientName);
    lier(ui->champMotif, &Patient::motif); lier(ui->champTel, &Patient::telephone); lier(ui->champNotes, &Patient::notes);

    
    auto lierDateHeure = [this](QLineEdit *champ, auto membre, const QString &format) {
        using T = std::decay_t<decltype(std::declval<Patient &>().*membre)>;
        connect(champ, &QLineEdit::editingFinished, this, [this, champ, membre, format]() {
            Patient *p = patientCourant();
            if (!p || !m_modeEdition) return;
            const T valeur = T::fromString(champ->text(), format);
            if (valeur.isValid()) p->*membre = valeur;
            else champ->setText((p->*membre).toString(format));
            majLigne(p->id);
        });
    };
    lierDateHeure(ui->champDate, &Patient::date, FORMAT_DATE); lierDateHeure(ui->champHeure, &Patient::heure, FORMAT_HEURE);

    auto lierLong = [this](QTextEdit *champ, QString Patient::*membre) {
        connect(champ, &QTextEdit::textChanged, this, [this, champ, membre]() {
            Patient *p = patientCourant();
            if (m_modeEdition && p) p->*membre = champ->toPlainText();
        });
    };
    lierLong(ui->motifText, &Patient::constatations); lierLong(ui->diagnosticText, &Patient::diagnostic);
}

void GestionRendezvous::configurerTri()
{
    const struct { const char *texte; int critere; } options[] = {
        {"Date/heure — plus tôt d'abord", HeureCroissante}, {"Date/heure — plus tard d'abord", HeureDecroissante},
        {"Motif — A → Z", MotifAZ}, {"Motif — Z → A", MotifZA}};
    auto *menu = new QMenu(ui->btnTrier);
    auto *groupe = new QActionGroup(menu);
    for (const auto &o : options) {
        QAction *a = menu->addAction(U(o.texte));
        a->setCheckable(true); a->setActionGroup(groupe); a->setChecked(o.critere == m_critereTri);
        connect(a, &QAction::triggered, this, [this, critere = o.critere]() { m_critereTri = critere; reconstruireListe(); });
    }
    ui->btnTrier->setMenu(menu);
}


int GestionRendezvous::ajouterPatient(const QString &nom, const QDate &date, const QTime &heure)
{
    Patient p;
    p.id = ++m_dernierId; p.dossier = numeroDossier(p.id);
    p.nom = nom; p.date = date; p.heure = heure;
    m_patients.append(p);
    return p.id;
}

Patient *GestionRendezvous::trouver(int id) { for (Patient &p : m_patients) if (p.id == id) return &p; return nullptr; }
Patient *GestionRendezvous::patientCourant() { return trouver(m_courant); }

void GestionRendezvous::nouveauPatient()
{
    const QTime t = QTime::currentTime();
    const int id = ajouterPatient(U("Nouveau patient"), QDate::currentDate(), QTime(t.hour(), t.minute()));
    reconstruireListe();
    modifierPatient(id);
}

void GestionRendezvous::modifierPatient(int id)
{
    if (!trouver(id)) return;
    selectionnerPatient(id); appliquerModeEdition(true);
    ui->patientName->setFocus(); ui->patientName->selectAll();
}

void GestionRendezvous::selectionnerPatient(int id)
{
    Patient *p = trouver(id);
    if (!p) return;
    appliquerModeEdition(false);
    m_courant = id;
    for (QPushButton *bouton : m_actions) bouton->setEnabled(true);
    if (auto *b = findChild<QPushButton *>(QString("btnPatient%1").arg(id))) b->setChecked(true);
    afficherPatient(*p);
}

void GestionRendezvous::afficherPatient(const Patient &p)
{
    const QSignalBlocker bloqueMotif(ui->motifText), bloqueDiagnostic(ui->diagnosticText);
    ui->patientName->setText(p.nom); ui->champNom->setText(p.nom);
    ui->champDate->setText(p.date.toString(FORMAT_DATE)); ui->champHeure->setText(p.heure.toString(FORMAT_HEURE));
    ui->champMotif->setText(p.motif); ui->champTel->setText(p.telephone);
    ui->champNotes->setText(p.notes); ui->motifText->setPlainText(p.constatations);
    ui->diagnosticText->setPlainText(p.diagnostic);
    ui->ownerLabel->setText(p.proprietaire.isEmpty()
        ? U("Propriétaire : —") : U("Propriétaire : %1").arg(p.proprietaire));
    ui->dossierLabel->setText(QString("Dossier #%1").arg(p.dossier));
}

void GestionRendezvous::appliquerModeEdition(bool actif)
{
    m_modeEdition = actif;
    for (QLineEdit *f : {ui->patientName, ui->champNom, ui->champDate, ui->champHeure, ui->champMotif, ui->champTel, ui->champNotes})
        f->setReadOnly(!actif);
    for (QTextEdit *f : {ui->motifText, ui->diagnosticText}) f->setReadOnly(!actif);
    ui->btnEnregistrer->setEnabled(actif);
    ui->btnEnregistrer->setText(actif ? "Enregistrer" : "Enregistré");
}


void GestionRendezvous::reconstruireListe()
{
    while (QLayoutItem *item = m_listeLayout->takeAt(0)) { delete item->widget(); delete item; }

    QVector<int> ordre;
    for (const Patient &p : m_patients)
        if (m_rechercheMotif.isEmpty() || p.motif.contains(m_rechercheMotif, Qt::CaseInsensitive)) ordre << p.id;
    std::stable_sort(ordre.begin(), ordre.end(), [this](int a, int b) { return avant(*trouver(a), *trouver(b), m_critereTri); });

    for (int id : ordre) {
        auto *ligne = new QWidget(m_patientsContainer);
        ligne->setFixedSize(262, 60);
        auto *ligneLayout = new QHBoxLayout(ligne);
        ligneLayout->setContentsMargins(0, 0, 0, 0); ligneLayout->setSpacing(3);
        auto creerBouton = [ligne, ligneLayout](const QString &texte, QSize taille, const QString &style) {
            auto *bouton = new QPushButton(texte, ligne);
            bouton->setCursor(Qt::PointingHandCursor); bouton->setFixedSize(taille); bouton->setStyleSheet(style);
            ligneLayout->addWidget(bouton);
            return bouton;
        };

        auto *b = creerBouton({}, {198, 60}, "QPushButton { background: transparent; color: #6B3F2E; border: none; "
            "text-align: left; padding-left: 55px; font-weight: bold; } QPushButton:checked { background: #F9DEE4; }");
        b->setObjectName(QString("btnPatient%1").arg(id)); b->setCheckable(true);
        m_groupe->addButton(b);
        connect(b, &QPushButton::clicked, this, [this, id]() { selectionnerPatient(id); });

        auto *supprimer = creerBouton(U("🗑"), {26, 28},
            "QPushButton { background: #FCE8E6; color: #B3261E; border: none; border-radius: 6px; font-size: 13px; }");
        supprimer->setToolTip(U("Supprimer le patient")); supprimer->setAccessibleName(U("Supprimer le patient"));
        connect(supprimer, &QPushButton::clicked, this, [this, id]() { supprimerPatient(id); });

        auto etiquette = [b](const QString &texte, QRect zone) {
            auto *l = new QLabel(texte, b);
            l->setGeometry(zone); l->setAlignment(Qt::AlignCenter); l->setAttribute(Qt::WA_TransparentForMouseEvents);
            return l;
        };
        etiquette(U("🐾"), {10, 12, 36, 36})->setStyleSheet("QLabel { background: #F3E6DC; border-radius: 18px; }");
        etiquette({}, {122, 20, 68, 20})->setObjectName(QString("statusPatient%1").arg(id));

        m_listeLayout->addWidget(ligne); ligne->show();
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
    const QString nom = p->nom.trimmed().isEmpty() ? U("(sans nom)") : p->nom;
    const QString ligne2 = QString("%1 • %2").arg(p->heure.toString(FORMAT_HEURE), p->motif.trimmed().isEmpty() ? U("—") : p->motif);
    b->setText(elide(nom, 65) + "\n" + elide(ligne2, 65));
    if (auto *st = findChild<QLabel *>(QString("statusPatient%1").arg(id))) {
        st->setText(p->statut); st->setStyleSheet(statusStyle(p->statutType));
    }
}

void GestionRendezvous::majCompteur()
{
    int enAttente = 0, realises = 0;
    for (const Patient &p : m_patients) { enAttente += p.statut == "En attente"; realises += p.rendezVousRealise; }
    const int total = m_patients.size();
    ui->patientsCountBadge->setText(QString("%1 en attente").arg(enAttente));
    ui->statTotalLabel->setText(U("Total des rendez-vous : %1").arg(total));
    ui->statRealisesLabel->setText(U("Réalisés : %1").arg(realises));
    ui->statARealiserLabel->setText(U("À réaliser : %1").arg(total - realises));
    m_graphiqueRendezVous->setAppointments(m_patients);
}


void GestionRendezvous::enregistrerPatient()
{
    Patient *patient = patientCourant();
    if (!patient || !m_modeEdition) return;
    QDate date; QTime heure;
    if (!validerChamp(this, ui->champDate, FORMAT_DATE, "Date invalide", "Saisissez une date valide avant d'enregistrer.", date)
        || !validerChamp(this, ui->champHeure, FORMAT_HEURE, "Heure invalide", "Saisissez une heure valide avant d'enregistrer.", heure))
        return;
    patient->date = date; patient->heure = heure;
    QString erreur;
    if (!m_patientModel.sauvegarder(*patient, erreur)) { echec(this, "Base de données", "Échec de l'enregistrement :\n%1", erreur); return; }
    reconstruireListe();
    selectionnerPatient(patient->id);
}

void GestionRendezvous::setStatutPatient(int numero, const QString &texte, const QString &type)
{
    Patient *p = trouver(numero);
    if (!p) return;
    const Patient ancien = *p;
    p->statut = texte; p->statutType = type;
    p->rendezVousRealise = type == "succes" || estRealise(texte);
    QString erreur;
    if (p->enBase && !m_patientModel.sauvegarder(*p, erreur)) {
        *p = ancien;
        echec(this, "Base de données", "Échec de la modification :\n%1", erreur);
        majLigne(numero);
        return;
    }
    majLigne(numero); majCompteur();
}

void GestionRendezvous::supprimerPatient(int id)
{
    Patient *patient = trouver(id);
    if (!patient) return;
    const QString nom = patient->nom.trimmed().isEmpty() ? U("ce patient") : patient->nom;
    if (QMessageBox::question(this, U("Supprimer le patient"), U("Voulez-vous vraiment supprimer %1 ?").arg(nom),
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes) return;
    QString erreur;
    if (!m_patientModel.supprimer(*patient, erreur)) { echec(this, "Base de données", "Échec de la suppression :\n%1", erreur); return; }
    m_patients.removeAt(int(patient - m_patients.data()));
    if (m_courant == id) m_courant = -1;

    reconstruireListe();
    if (!m_patients.isEmpty()) { selectionnerPatient(m_patients.first().id); return; }

    afficherPatient(Patient());     
    ui->dossierLabel->setText(U("Aucun dossier sélectionné"));
    appliquerModeEdition(false);
    for (QPushButton *bouton : m_actions) bouton->setEnabled(false);
}

void GestionRendezvous::exporterPreConsultationPdf()
{
    const Patient *patient = patientCourant();
    if (!patient) { QMessageBox::warning(this, U("Aucun patient"), U("Sélectionnez un patient avant l'export.")); return; }
    QString chemin = QFileDialog::getSaveFileName(this, U("Exporter la pré-consultation"),
        QDir::home().filePath(QString("preconsultation_%1.pdf").arg(patient->dossier)), U("Fichier PDF (*.pdf)"));
    if (chemin.isEmpty()) return;
    if (!chemin.endsWith(".pdf", Qt::CaseInsensitive)) chemin += ".pdf";

    QSaveFile fichierPdf(chemin);
    if (!fichierPdf.open(QIODevice::WriteOnly)) {
        echec(this, "Échec de l'export", "Impossible de créer le fichier PDF : %1", fichierPdf.errorString()); return;
    }
    const QPair<QString, QString> fields[] = {
        {"Nom de l'animal", patient->nom},
        {"Date et heure du rendez-vous", patient->date.toString(FORMAT_DATE) + " à " + patient->heure.toString(FORMAT_HEURE)},
        {"Téléphone du propriétaire", patient->telephone}, {"Motif de la consultation", patient->motif},
        {"Notes communiquées", patient->notes}, {"Constatations préalables", patient->constatations}};
    QStringList rows;
    for (const auto &[label, raw] : fields)
        rows << QString("<p><b>%1</b><br>%2</p>").arg(label,
            (raw.trimmed().isEmpty() ? U("Non renseigné") : raw.trimmed()).toHtmlEscaped().replace("\n", "<br>"));
    QTextDocument document;
    document.setHtml(QString("<h1>Questionnaire de pré-consultation</h1>"
        "<p>Dossier : %1 | Exporté le : %2</p><h2>Informations et pré-consultation</h2>%3")
        .arg(patient->dossier.toHtmlEscaped(), QDate::currentDate().toString(FORMAT_DATE), rows.join(QString())));
    document.setDocumentMargin(48);
    {
        QPdfWriter writer(&fichierPdf);
        writer.setPageSize(QPageSize(QPageSize::A4)); writer.setResolution(96);
        document.print(&writer);
    }
    if (!fichierPdf.commit()) {
        echec(this, "Échec de l'export", "Impossible d'enregistrer le PDF : %1", fichierPdf.errorString()); return;
    }
    QMessageBox::information(this, U("Export terminé"), U("Le questionnaire de pré-consultation a été enregistré."));
}


static QString chiffresSeulement(const QString &texte)
{
    QString resultat;
    for (const QChar c : texte) if (c.isDigit()) resultat += c;
    return resultat;
}

static bool executer(QSqlQuery &query, QString &erreur)
{
    if (query.exec()) return true;
    erreur = query.lastError().text(); return false;
}

static bool executer(QSqlQuery &query, QSqlDatabase &database, QString &erreur,
                     const char *messageSiAucuneLigne = nullptr)
{
    if (!executer(query, erreur)) {
        database.rollback();
        return false;
    }
    if (!messageSiAucuneLigne || query.numRowsAffected() != 0) return true;
    erreur = U(messageSiAucuneLigne);
    database.rollback();
    return false;
}

static bool invalide(QString &erreur, const char *message) { erreur = U(message); return false; }

bool PatientModel::charger(QVector<Patient> &patients, QString &erreur)
{
    QSqlQuery query;
    query.prepare(QString(
        "SELECT r.ID_ANIMAL, TO_CHAR(r.HEURE, '%1'), TO_CHAR(r.DATE_RENDEZ_VOUS, '%2'), "
        "TO_CHAR(r.TELEPHONE), r.ETAT, r.MOTIF, "
        "NVL(r.PROPRIETAIRE, a.NOM_PROPRIETAIRE), a.NOM "
        "FROM GESTIONRENDEZVOUS r "
        "JOIN ANIMAUX a ON a.ID_ANIMAL = r.ID_ANIMAL "
        "ORDER BY r.DATE_RENDEZ_VOUS, r.HEURE")
        .arg(SQL_FORMAT_HEURE, SQL_FORMAT_DATE));
    if (!executer(query, erreur)) return false;

    QVector<Patient> resultat;
    while (query.next()) {
        Patient p;
        p.id = resultat.size() + 1;
        p.idAnimal = query.value(0).toLongLong();
        const QString heure = query.value(1).toString();
        const QString date = query.value(2).toString();
        p.telephone = query.value(3).toString();
        p.date = QDate::fromString(date, "yyyy-MM-dd");
        p.heure = QTime::fromString(heure.mid(11, 5), "HH:mm");
        if (!p.date.isValid() || !p.heure.isValid()) return invalide(erreur, "La base contient une date ou une heure invalide.");
        p.dossier = numeroDossier(p.id);
        p.cleTelephone = p.telephone;
        p.statut = query.value(4).toString();
        p.motif = query.value(5).toString();
        p.proprietaire = query.value(6).toString();
        p.nom = query.value(7).toString();
        const QString statut = p.statut.toLower();
        p.rendezVousRealise = estRealise(statut);
        p.statutType = p.rendezVousRealise ? "succes" : statut.contains("urgent") || statut.contains("annul") ? "alerte" : "neutre";
        p.enBase = true;
        resultat.append(p);
    }
    if (query.lastError().isValid()) { erreur = query.lastError().text(); return false; }
    patients = resultat;
    return true;
}

bool PatientModel::sauvegarder(Patient &patient, QString &erreur)
{
    if (patient.nom.trimmed().isEmpty() || patient.nom.toUtf8().size() > 100)
        return invalide(erreur, "Saisissez un nom d'animal (100 caractères maximum).");
    for (const QChar c : patient.telephone)
        if (!c.isDigit() && !QStringLiteral(" +().-/").contains(c))
            return invalide(erreur, "Le numéro de téléphone contient un caractère invalide.");
    const QString telephone = chiffresSeulement(patient.telephone);
    if (!patient.date.isValid() || !patient.heure.isValid()) return invalide(erreur, "Saisissez une date et une heure valides.");
    bool telephoneValide = false;
    const qulonglong numeroTelephone = telephone.toULongLong(&telephoneValide);
    if (!telephoneValide || numeroTelephone == 0 || telephone.size() > 15)
        return invalide(erreur, "Saisissez un numéro de téléphone positif (15 chiffres maximum).");
    if (patient.motif.toUtf8().size() > 200 || patient.statut.trimmed().isEmpty() || patient.statut.size() > 50
        || (!patient.proprietaire.isEmpty() && patient.proprietaire.toUtf8().size() > 150))
        return invalide(erreur, "Vérifiez le motif, le propriétaire et le statut du rendez-vous.");

    const QString date = patient.date.toString("yyyy-MM-dd");
    const QString heure = date + " " + patient.heure.toString("HH:mm") + ":00.000000";
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.transaction()) {
        erreur = database.lastError().text();
        return false;
    }
    QSqlQuery query;
    if (!patient.enBase) {
        query.prepare(QString("BEGIN ENREGISTRER_RENDEZVOUS(?, TO_NUMBER(?), "
                              "TO_TIMESTAMP(?, '%1'), ?, TO_DATE(?, '%2'), ?); END;")
                      .arg(SQL_FORMAT_HEURE, SQL_FORMAT_DATE));
        query.addBindValue(patient.nom.trimmed());
        query.addBindValue(telephone);
        query.addBindValue(heure);
        query.addBindValue(patient.statut);
        query.addBindValue(date);
        query.addBindValue(patient.motif);
        if (!executer(query, database, erreur)) return false;
        query.finish();
        query.prepare("SELECT ID_ANIMAL, NOM_PROPRIETAIRE FROM ANIMAUX "
                      "WHERE LOWER(NOM) = LOWER(?) AND TELEPHONE = TO_NUMBER(?)");
        query.addBindValue(patient.nom.trimmed());
        query.addBindValue(telephone);
        if (!executer(query, database, erreur) || !query.next()) {
            if (erreur.isEmpty()) erreur = U("L'animal n'a pas été retrouvé après son enregistrement.");
            database.rollback();
            return false;
        }
        patient.idAnimal = query.value(0).toLongLong();
        patient.proprietaire = query.value(1).toString();
        if (patient.proprietaire.toUtf8().size() > 150) {
            erreur = U("L'animal sélectionné n'a pas de propriétaire valide dans la base.");
            database.rollback();
            return false;
        }
        if (query.next()) {
            erreur = U("Plusieurs animaux correspondent au même nom et téléphone.");
            database.rollback();
            return false;
        }
    } else {
        query.prepare(QString("BEGIN MODIFIER_RENDEZVOUS(?, TO_NUMBER(?), ?, TO_NUMBER(?), "
                              "TO_TIMESTAMP(?, '%1'), ?, TO_DATE(?, '%2'), ?, ?); END;")
                      .arg(SQL_FORMAT_HEURE, SQL_FORMAT_DATE));
        query.addBindValue(patient.idAnimal);
        query.addBindValue(patient.cleTelephone);
        query.addBindValue(patient.nom.trimmed());
        query.addBindValue(telephone);
        query.addBindValue(heure);
        query.addBindValue(patient.statut);
        query.addBindValue(date);
        query.addBindValue(patient.motif);
        query.addBindValue(patient.proprietaire);
        if (!executer(query, database, erreur)) return false;
    }
    query.finish();
    if (!database.commit()) {
        erreur = database.lastError().text();
        database.rollback();
        return false;
    }

    patient.enBase = true;
    patient.telephone = telephone;
    patient.cleTelephone = telephone;
    patient.dossier = numeroDossier(patient.id);
    return true;
}

bool PatientModel::supprimer(const Patient &patient, QString &erreur)
{
    if (!patient.enBase) return true;
    QSqlQuery query;
    query.prepare("DELETE FROM GESTIONRENDEZVOUS WHERE ID_ANIMAL = ? AND TELEPHONE = TO_NUMBER(?)");
    query.addBindValue(patient.idAnimal);
    query.addBindValue(patient.cleTelephone);
    if (!executer(query, erreur)) return false;
    return query.numRowsAffected() > 0 || invalide(erreur, "Le rendez-vous n'existe plus dans la base de données.");
}

void GestionRendezvous::chargerDepuisBase()
{
    QString erreur;
    if (!m_patientModel.charger(m_patients, erreur)) {
        qCritical() << "Chargement des rendez-vous impossible :" << erreur;
        echec(this, "Base de données", "Impossible de charger les rendez-vous :\n%1", erreur);
        return;
    }
    m_dernierId = m_patients.size();
}
