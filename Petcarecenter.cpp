#include "petcarecenter.h"
#include "ui_petcarecenter.h" // Le fichier UI généré

#include <QDate>
#include <QDateTime>
#include <QFileDialog>
#include <QHeaderView>
#include <QLabel>
#include <QMap>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPushButton>
#include <QStyle>
#include <QTextDocument>
#include <QVBoxLayout>
#include <algorithm>

namespace {
QString clean(const QString &s) { return s.trimmed().toLower(); }
void warning(QWidget *w, const QString &title, const QString &text)
{ QMessageBox::warning(w, title, text); }
}

Petcarecenter::Petcarecenter(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Petcarecenter), m_domainStatsLabel(nullptr),
    m_sortAscNom(true), m_sortAscPoste(true)
{
    ui->setupUi(this);

    // --- Stats label dans widgetCurve ---
    auto *layout = new QVBoxLayout(ui->widgetCurve);
    m_domainStatsLabel = new QLabel(ui->widgetCurve);
    m_domainStatsLabel->setAlignment(Qt::AlignCenter);
    m_domainStatsLabel->setStyleSheet("color:#7D6658;font-size:11px;");
    layout->addWidget(m_domainStatsLabel);

    // --- Boutons de navigation ---
    const QList<QPushButton *> nav{ui->btnNavAnimaux, ui->btnNavCommandes,
                                   ui->btnNavSoins, ui->btnNavProduits, ui->btnNavPaiements};
    for (auto *button : nav) {
        button->setCursor(Qt::PointingHandCursor);
        button->setProperty("active", button == ui->btnNavCommandes);
        connect(button, &QPushButton::clicked, this, [nav, button] {
            for (auto *b : nav) {
                b->setProperty("active", b == button);
                b->style()->unpolish(b); b->style()->polish(b); b->update();
            }
        });
    }

    // --- Configuration initiale de l'UI ---
    setWindowTitle("Pawché - Gestion des employés");
    ui->comboFilterType->setItemText(0, "Tous les employés");
    ui->btnTrierPrix->setText("↕ Trier par nom");
    ui->btnTrierDate->setText("↕ Trier par poste");
    ui->lblAlertHeading->setText("Employés enregistrés");

    ui->tableCommandes->setColumnCount(5);
    ui->tableCommandes->setHorizontalHeaderLabels(
        {"ID employé", "Nom", "Prénom", "Téléphone", "Mail"});
    for (int i = 0; i < 4; ++i)
        ui->tableCommandes->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    ui->txtId->setReadOnly(true);
    ui->txtId->setPlaceholderText("Auto-généré");
    ui->txtId->setToolTip("Identifiant généré automatiquement (EMP-XXXXX)");

    // --- Chargement ---
    loadEmployes();
    refreshTable();
    updateStatistics();
    ui->txtId->setText(Employe::genererId());
}

Petcarecenter::~Petcarecenter() { delete ui; }

void Petcarecenter::loadEmployes()
{
    m_employes = Employe::chargerTous();
}

int Petcarecenter::employeIndex(const QString &id) const
{
    for (int i = 0; i < m_employes.size(); ++i)
        if (m_employes[i].getId().compare(id, Qt::CaseInsensitive) == 0) return i;
    return -1;
}

Employe Petcarecenter::employeFromForm() const
{
    return Employe(
        ui->txtId->text().trimmed(),
        ui->lineEdit->text().trimmed(),
        ui->lineEdit_2->text().trimmed(),
        ui->lineEdit_3->text().trimmed(),
        ui->lineEdit_4->text().trimmed(),
        ui->lineEdit_5->text().trimmed(),
        ui->dateEditEmbauche->date().toString("dd/MM/yyyy"),
        ui->comboPoste->currentText(),
        ui->dateEditNaissance->date().toString("dd/MM/yyyy"),
        ui->lineEditMotDePasse->text(),
        ui->comboQuestion->currentText(),
        ui->lineEditReponse->text()
        );
}

bool Petcarecenter::formIsValid()
{
    const auto e = employeFromForm();
    if (e.getNom().isEmpty() || e.getPrenom().isEmpty() ||
        e.getTelephone().isEmpty() || e.getMail().isEmpty()) {
        warning(this, "Champs requis", "Remplissez tous les champs de l'employé.");
        return false;
    }
    if (!e.getMail().contains('@') || !e.getMail().section('@', 1).contains('.')) {
        warning(this, "E-mail invalide", "Saisissez une adresse e-mail valide.");
        ui->lineEdit_4->setFocus();
        return false;
    }
    return true;
}

QList<Employe> Petcarecenter::currentFilteredList() const
{
    const QString q = clean(ui->inputSearch->text());
    const QString filter = ui->comboFilterType->currentText();
    QList<Employe> result;

    for (const auto &e : m_employes) {
        const QString mail = clean(e.getMail());
        const bool gmail   = mail.endsWith("@gmail.com");
        const bool outlook = mail.endsWith("@outlook.com") || mail.endsWith("@hotmail.com");
        const bool yahoo   = mail.endsWith("@yahoo.com");
        const bool provider = filter == "Tous les employés" || (filter == "Gmail" && gmail)
                              || (filter == "Outlook" && outlook) || (filter == "Yahoo" && yahoo)
                              || (filter == "Autres domaines" && !gmail && !outlook && !yahoo);
        const bool matches = q.isEmpty() || clean(e.getId()).contains(q)
                             || clean(e.getNom()).contains(q) || clean(e.getPrenom()).contains(q)
                             || clean(e.getTelephone()).contains(q) || mail.contains(q);
        if (provider && matches) result.append(e);
    }
    return result;
}

void Petcarecenter::refreshTable()
{
    auto *table = ui->tableCommandes;
    table->setRowCount(0);
    for (const auto &e : currentFilteredList()) {
        const int row = table->rowCount();
        table->insertRow(row);
        const QStringList cells{e.getId(), e.getNom(), e.getPrenom(),
                                e.getTelephone(), e.getMail()};
        for (int col = 0; col < cells.size(); ++col) {
            auto *item = new QTableWidgetItem(cells[col]);
            if (col < 4) item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }
    }
}

void Petcarecenter::updateStatistics()
{
    QMap<QString, int> annees;
    int emails = 0;
    for (const auto &e : m_employes) {
        const QString domain = e.getMail().section('@', 1).toLower();
        if (!domain.isEmpty()) ++emails;
        const QString annee = e.getDateEmbauche().right(4);
        if (!annee.isEmpty() && annee.toInt() > 1900) ++annees[annee];
    }
    QStringList lines;
    for (auto i = annees.cbegin(); i != annees.cend(); ++i)
        lines << QString("%1 : %2").arg(i.key()).arg(i.value());
    m_domainStatsLabel->setText(lines.isEmpty() ? "Aucune donnée disponible" : lines.join('\n'));

    ui->lblAlertBadge->setText(QString::number(m_employes.size()));
    ui->lblAlertDesc->setText(m_employes.size() == 1 ? "employé enregistré" : "employés enregistrés");
    ui->lblTotalMontant->setText(QString("Avec e-mail : %1").arg(emails));
}

void Petcarecenter::clearForm()
{
    for (auto *field : {ui->txtId, ui->lineEdit, ui->lineEdit_2, ui->lineEdit_3,
                        ui->lineEdit_4, ui->lineEdit_5, ui->lineEditMotDePasse,
                        ui->lineEditReponse})
        field->clear();
    ui->dateEditEmbauche->setDate(QDate::currentDate());
    ui->dateEditNaissance->setDate(QDate::currentDate());
    ui->comboPoste->setCurrentIndex(0);
    ui->comboQuestion->setCurrentIndex(0);

    ui->txtId->setReadOnly(true);
    ui->txtId->setText(Employe::genererId());
    ui->lineEdit->setFocus();
    ui->tableCommandes->clearSelection();
}

void Petcarecenter::on_btnAjouter_clicked()
{
    if (!formIsValid()) return;

    if (Employe::idExiste(ui->txtId->text().trimmed()))
        ui->txtId->setText(Employe::genererId());

    Employe e = employeFromForm();

    if (e.ajouter()) {
        m_employes.append(e);
        refreshTable();
        updateStatistics();
        clearForm();
        QMessageBox::information(this, "Succès", "Employé ajouté dans la base de données !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé.");
    }
}

void Petcarecenter::on_btnModifier_clicked()
{
    const int row = ui->tableCommandes->currentRow();
    if (row < 0 || !ui->tableCommandes->item(row, 0)) {
        warning(this, "Sélection requise", "Sélectionnez un employé.");
        return;
    }
    if (!formIsValid()) return;

    const int index = employeIndex(ui->tableCommandes->item(row, 0)->text());
    if (index < 0) return;

    Employe e = employeFromForm();

    if (e.modifier()) {
        m_employes[index] = e;
        refreshTable();
        updateStatistics();
        QMessageBox::information(this, "Succès", "Employé modifié !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void Petcarecenter::on_btnSupprimer_clicked()
{
    const int row = ui->tableCommandes->currentRow();
    if (row < 0 || !ui->tableCommandes->item(row, 0)) {
        warning(this, "Sélection requise", "Sélectionnez un employé.");
        return;
    }
    const QString id = ui->tableCommandes->item(row, 0)->text();
    if (QMessageBox::question(this, "Confirmation", "Supprimer l'employé " + id + " ?")
        != QMessageBox::Yes) return;

    if (Employe::supprimer(id)) {
        const int index = employeIndex(id);
        if (index >= 0) m_employes.removeAt(index);
        refreshTable();
        updateStatistics();
        clearForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression.");
    }
}

void Petcarecenter::on_btnVider_clicked() { clearForm(); }

void Petcarecenter::on_tableCommandes_cellClicked(int row, int)
{
    if (row < 0 || !ui->tableCommandes->item(row, 0)) return;
    const int i = employeIndex(ui->tableCommandes->item(row, 0)->text());
    if (i < 0) return;
    const auto &e = m_employes[i];

    ui->txtId->setText(e.getId());
    ui->txtId->setReadOnly(true);
    ui->lineEdit->setText(e.getNom());
    ui->lineEdit_2->setText(e.getPrenom());
    ui->lineEdit_3->setText(e.getTelephone());
    ui->lineEdit_4->setText(e.getMail());
    ui->lineEdit_5->setText(e.getAdresse());

    const QDate dEmb = QDate::fromString(e.getDateEmbauche(), "dd/MM/yyyy");
    if (dEmb.isValid()) ui->dateEditEmbauche->setDate(dEmb);

    ui->comboPoste->setCurrentText(e.getPoste());

    const QDate dNais = QDate::fromString(e.getDateNaissance(), "dd/MM/yyyy");
    if (dNais.isValid()) ui->dateEditNaissance->setDate(dNais);

    ui->lineEditMotDePasse->setText(e.getMotDePasse());
    ui->comboQuestion->setCurrentText(e.getQuestionSecrete());
    ui->lineEditReponse->setText(e.getReponse());
}

void Petcarecenter::on_btnTrierPrix_clicked()
{
    std::sort(m_employes.begin(), m_employes.end(), [this](const auto &a, const auto &b) {
        const int c = QString::compare(a.getNom(), b.getNom(), Qt::CaseInsensitive);
        return m_sortAscNom ? c < 0 : c > 0;
    });
    m_sortAscNom = !m_sortAscNom;
    ui->btnTrierPrix->setText(m_sortAscNom ? "↕ Trier par nom" : "↕ Nom décroissant");
    refreshTable();
}

void Petcarecenter::on_btnTrierDate_clicked()
{
    std::sort(m_employes.begin(), m_employes.end(), [this](const auto &a, const auto &b) {
        const int c = QString::compare(a.getPoste(), b.getPoste(), Qt::CaseInsensitive);
        return m_sortAscPoste ? c < 0 : c > 0;
    });
    m_sortAscPoste = !m_sortAscPoste;
    ui->btnTrierDate->setText(m_sortAscPoste ? "↕ Trier par poste" : "↕ Poste décroissant");
    refreshTable();
}

void Petcarecenter::on_inputSearch_textChanged(const QString &) { refreshTable(); }
void Petcarecenter::on_comboFilterType_currentTextChanged(const QString &) { refreshTable(); }

void Petcarecenter::on_btnExportPdf_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Exporter les employés en PDF",
                                                "Employes.pdf", "PDF (*.pdf)");
    if (path.isEmpty()) return;
    if (!path.endsWith(".pdf", Qt::CaseInsensitive)) path += ".pdf";

    const auto list = currentFilteredList();
    QString html = "<h2 style='text-align:center'>Pawché - Employés</h2><p>";
    html += QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + " · "
            + QString::number(list.size()) + " employé(s)</p>";
    html += "<table width='100%' border='1' cellspacing='0' cellpadding='6'>"
            "<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Téléphone</th><th>Mail</th></tr>";
    for (const auto &e : list)
        html += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
                    .arg(e.getId().toHtmlEscaped(), e.getNom().toHtmlEscaped(),
                         e.getPrenom().toHtmlEscaped(), e.getTelephone().toHtmlEscaped(),
                         e.getMail().toHtmlEscaped());

    QTextDocument doc; doc.setHtml(html + "</table>");
    QPdfWriter writer(path);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    doc.print(&writer);
    QMessageBox::information(this, "Exportation réussie", "PDF créé :\n" + path);
}