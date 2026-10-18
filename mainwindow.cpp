#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrcodegenerator.h"
#include "connection.h"

#include <QDate>
#include <QDateTime>
#include <QFileDialog>
#include <QHeaderView>
#include <QLabel>
#include <QMap>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QStyle>
#include <QTextDocument>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <algorithm>

namespace {
QString clean(const QString &s) { return s.trimmed().toLower(); }
void warning(QWidget *w, const QString &title, const QString &text)
{ QMessageBox::warning(w, title, text); }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_domainStatsLabel(nullptr),
    m_sortAscNom(true), m_sortAscPoste(true)
{
    ui->setupUi(this);

    auto *layout = new QVBoxLayout(ui->widgetCurve);
    m_domainStatsLabel = new QLabel(ui->widgetCurve);
    m_domainStatsLabel->setAlignment(Qt::AlignCenter);
    m_domainStatsLabel->setStyleSheet("color:#7D6658;font-size:11px;");
    layout->addWidget(m_domainStatsLabel);

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

    setWindowTitle("Pawché - Gestion des employés");
    ui->comboFilterType->setItemText(0, "Tous les employés");
    ui->btnTrierPrix->setText("↕ Trier par nom");
    ui->btnTrierDate->setText("↕ Trier par poste");
    ui->lblAlertHeading->setText("Employés enregistrés");
    ui->tableCommandes->setColumnCount(5);
    ui->tableCommandes->setHorizontalHeaderLabels({"ID employé", "Nom", "Prénom", "Téléphone", "Mail"});
    for (int i = 0; i < 4; ++i)
        ui->tableCommandes->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    ui->txtId->setReadOnly(true);
    ui->txtId->setPlaceholderText("Auto-généré");
    ui->txtId->setToolTip("Identifiant généré automatiquement (EMP-XXXXX)");

    loadEmployes();
    refreshTable();
    updateStatistics();

    ui->txtId->setText(generateEmployeId());
    ui->lblQrImage->setText("Sélectionnez un employé");
    ui->lblQrInfo->clear();
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::generateEmployeId() const
{
    QString id;
    do {
        id = QString("EMP-%1").arg(QRandomGenerator::global()->bounded(10000, 100000));
    } while (employeIndex(id) >= 0);
    return id;
}

// --- REQUETES SQL ---
void MainWindow::loadEmployes()
{
    m_employes.clear();
    QSqlQuery query(Connection::createInstance().createConnection() ? QSqlDatabase::database() : QSqlDatabase());

    if (query.exec("SELECT * FROM EMPLOYES")) {
        while (query.next()) {
            Employe e;
            e.id = query.value("ID").toString();
            e.nom = query.value("NOM").toString();
            e.prenom = query.value("PRENOM").toString();
            e.telephone = query.value("TELEPHONE").toString();
            e.mail = query.value("MAIL").toString();
            e.adresse = query.value("ADRESSE").toString();
            e.dateEmbauche = query.value("DATE_EMBAUCHE").toString();
            e.poste = query.value("POSTE").toString();
            e.dateNaissance = query.value("DATE_NAISSANCE").toString();
            e.motDePasse = query.value("MOT_DE_PASSE").toString();
            e.questionSecrete = query.value("QUESTION_SECRETE").toString();
            e.reponse = query.value("REPONSE").toString();
            m_employes.append(e);
        }
    } else {
        qDebug() << "Erreur SELECT:" << query.lastError().text();
    }
}

bool MainWindow::addEmployeToDb(const Employe &e)
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, TELEPHONE, MAIL, ADRESSE, DATE_EMBAUCHE, POSTE, DATE_NAISSANCE, MOT_DE_PASSE, QUESTION_SECRETE, REPONSE) "
                  "VALUES (:id, :nom, :prenom, :telephone, :mail, :adresse, :dateEmbauche, :poste, :dateNaissance, :motDePasse, :questionSecrete, :reponse)");
    query.bindValue(":id", e.id); query.bindValue(":nom", e.nom); query.bindValue(":prenom", e.prenom);
    query.bindValue(":telephone", e.telephone); query.bindValue(":mail", e.mail); query.bindValue(":adresse", e.adresse);
    query.bindValue(":dateEmbauche", e.dateEmbauche); query.bindValue(":poste", e.poste); query.bindValue(":dateNaissance", e.dateNaissance);
    query.bindValue(":motDePasse", e.motDePasse); query.bindValue(":questionSecrete", e.questionSecrete); query.bindValue(":reponse", e.reponse);

    if (query.exec()) return true;
    QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
    return false;
}

bool MainWindow::updateEmployeInDb(const Employe &e)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET NOM=:nom, PRENOM=:prenom, TELEPHONE=:telephone, MAIL=:mail, ADRESSE=:adresse, "
                  "DATE_EMBAUCHE=:dateEmbauche, POSTE=:poste, DATE_NAISSANCE=:dateNaissance, MOT_DE_PASSE=:motDePasse, "
                  "QUESTION_SECRETE=:questionSecrete, REPONSE=:reponse WHERE ID=:id");
    query.bindValue(":nom", e.nom); query.bindValue(":prenom", e.prenom); query.bindValue(":telephone", e.telephone);
    query.bindValue(":mail", e.mail); query.bindValue(":adresse", e.adresse); query.bindValue(":dateEmbauche", e.dateEmbauche);
    query.bindValue(":poste", e.poste); query.bindValue(":dateNaissance", e.dateNaissance); query.bindValue(":motDePasse", e.motDePasse);
    query.bindValue(":questionSecrete", e.questionSecrete); query.bindValue(":reponse", e.reponse); query.bindValue(":id", e.id);

    if (query.exec()) return true;
    QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
    return false;
}

bool MainWindow::deleteEmployeFromDb(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);
    if (query.exec()) return true;
    QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
    return false;
}

// --- GESTION INTERFACE ---

int MainWindow::employeIndex(const QString &id) const
{
    for (int i = 0; i < m_employes.size(); ++i)
        if (m_employes[i].id.compare(id, Qt::CaseInsensitive) == 0) return i;
    return -1;
}

Employe MainWindow::employeFromForm() const
{
    Employe e;
    e.id              = ui->txtId->text().trimmed();
    e.nom             = ui->lineEdit->text().trimmed();
    e.prenom          = ui->lineEdit_2->text().trimmed();
    e.telephone       = ui->lineEdit_3->text().trimmed();
    e.mail            = ui->lineEdit_4->text().trimmed();
    e.adresse         = ui->lineEdit_5->text().trimmed();
    e.dateEmbauche    = ui->dateEditEmbauche->date().toString("dd/MM/yyyy");
    e.poste           = ui->comboPoste->currentText();
    e.dateNaissance   = ui->dateEditNaissance->date().toString("dd/MM/yyyy");
    e.motDePasse      = ui->lineEditMotDePasse->text();
    e.questionSecrete = ui->comboQuestion->currentText();
    e.reponse         = ui->lineEditReponse->text();
    return e;
}

bool MainWindow::formIsValid()
{
    const auto e = employeFromForm();
    if (e.nom.isEmpty() || e.prenom.isEmpty() || e.telephone.isEmpty() || e.mail.isEmpty()) {
        warning(this, "Champs requis", "Remplissez tous les champs de l'employé."); return false;
    }
    if (!e.mail.contains('@') || !e.mail.section('@', 1).contains('.')) {
        warning(this, "E-mail invalide", "Saisissez une adresse e-mail valide.");
        ui->lineEdit_4->setFocus(); return false;
    }
    return true;
}

QList<Employe> MainWindow::currentFilteredList() const
{
    const QString q = clean(ui->inputSearch->text()), filter = ui->comboFilterType->currentText();
    QList<Employe> result;
    for (const auto &e : m_employes) {
        const QString mail = clean(e.mail);
        const bool gmail   = mail.endsWith("@gmail.com");
        const bool outlook = mail.endsWith("@outlook.com") || mail.endsWith("@hotmail.com");
        const bool yahoo   = mail.endsWith("@yahoo.com");
        const bool provider = filter == "Tous les employés" || (filter == "Gmail" && gmail)
                              || (filter == "Outlook" && outlook) || (filter == "Yahoo" && yahoo)
                              || (filter == "Autres domaines" && !gmail && !outlook && !yahoo);
        const bool matches = q.isEmpty() || clean(e.id).contains(q) || clean(e.nom).contains(q)
                             || clean(e.prenom).contains(q) || clean(e.telephone).contains(q) || mail.contains(q);
        if (provider && matches) result.append(e);
    }
    return result;
}

void MainWindow::refreshTable()
{
    auto *table = ui->tableCommandes;
    table->setRowCount(0);
    for (const auto &e : currentFilteredList()) {
        const int row = table->rowCount(); table->insertRow(row);
        const QStringList cells{e.id, e.nom, e.prenom, e.telephone, e.mail};
        for (int col = 0; col < cells.size(); ++col) {
            auto *item = new QTableWidgetItem(cells[col]);
            if (col < 4) item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }
    }
}

void MainWindow::updateStatistics()
{
    QMap<QString, int> annees;
    int emails = 0;
    for (const auto &e : m_employes) {
        const QString domain = e.mail.section('@', 1).toLower();
        if (!domain.isEmpty()) ++emails;
        const QString annee = e.dateEmbauche.right(4);
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

void MainWindow::clearForm()
{
    for (auto *field : {ui->txtId, ui->lineEdit, ui->lineEdit_2, ui->lineEdit_3, ui->lineEdit_4,
                        ui->lineEdit_5, ui->lineEditMotDePasse, ui->lineEditReponse})
        field->clear();
    ui->dateEditEmbauche->setDate(QDate::currentDate());
    ui->dateEditNaissance->setDate(QDate::currentDate());
    ui->comboPoste->setCurrentIndex(0);
    ui->comboQuestion->setCurrentIndex(0);

    ui->txtId->setReadOnly(true);
    ui->txtId->setText(generateEmployeId());
    ui->lineEdit->setFocus();
    ui->tableCommandes->clearSelection();

    ui->lblQrImage->setText("Sélectionnez un employé");
    ui->lblQrInfo->clear();
}

void MainWindow::on_btnAjouter_clicked()
{
    if (!formIsValid()) return;
    if (employeIndex(ui->txtId->text().trimmed()) >= 0)
        ui->txtId->setText(generateEmployeId());

    const auto e = employeFromForm();

    if (addEmployeToDb(e)) {
        m_employes.append(e);
        refreshTable();
        updateStatistics();
        clearForm();
        QMessageBox::information(this, "Succès", "Employé ajouté dans la base de données !");
    }
}

void MainWindow::on_btnModifier_clicked()
{
    const int row = ui->tableCommandes->currentRow();
    if (row < 0 || !ui->tableCommandes->item(row, 0)) {
        warning(this, "Sélection requise", "Sélectionnez un employé."); return;
    }
    if (!formIsValid()) return;
    const int index = employeIndex(ui->tableCommandes->item(row, 0)->text());
    if (index < 0) return;

    const auto e = employeFromForm();

    if (updateEmployeInDb(e)) {
        m_employes[index] = e;
        refreshTable();
        updateStatistics();
        updateQrForEmploye(e);
        QMessageBox::information(this, "Succès", "Employé modifié !");
    }
}

void MainWindow::on_btnSupprimer_clicked()
{
    const int row = ui->tableCommandes->currentRow();
    if (row < 0 || !ui->tableCommandes->item(row, 0)) {
        warning(this, "Sélection requise", "Sélectionnez un employé."); return;
    }
    const QString id = ui->tableCommandes->item(row, 0)->text();
    if (QMessageBox::question(this, "Confirmation", "Supprimer l'employé " + id + " ?") != QMessageBox::Yes) return;

    if (deleteEmployeFromDb(id)) {
        const int index = employeIndex(id);
        if (index >= 0) m_employes.removeAt(index);
        refreshTable();
        updateStatistics();
        clearForm();
    }
}

void MainWindow::on_btnVider_clicked() { clearForm(); }

void MainWindow::on_tableCommandes_cellClicked(int row, int)
{
    if (row < 0 || !ui->tableCommandes->item(row, 0)) return;
    const int i = employeIndex(ui->tableCommandes->item(row, 0)->text());
    if (i < 0) return;
    const auto &e = m_employes[i];
    ui->txtId->setText(e.id);
    ui->txtId->setReadOnly(true);
    ui->lineEdit->setText(e.nom);
    ui->lineEdit_2->setText(e.prenom);
    ui->lineEdit_3->setText(e.telephone);
    ui->lineEdit_4->setText(e.mail);
    ui->lineEdit_5->setText(e.adresse);

    const QDate dEmb = QDate::fromString(e.dateEmbauche, "dd/MM/yyyy");
    if (dEmb.isValid()) ui->dateEditEmbauche->setDate(dEmb);

    ui->comboPoste->setCurrentText(e.poste);

    const QDate dNais = QDate::fromString(e.dateNaissance, "dd/MM/yyyy");
    if (dNais.isValid()) ui->dateEditNaissance->setDate(dNais);

    ui->lineEditMotDePasse->setText(e.motDePasse);
    ui->comboQuestion->setCurrentText(e.questionSecrete);
    ui->lineEditReponse->setText(e.reponse);

    updateQrForEmploye(e);
}

// --- UTILISATION DU GENERATEUR DE QR CODE ---
void MainWindow::updateQrForEmploye(const Employe &e)
{
    const QString data = QString(
                             "Pawché - Fiche Employé\n"
                             "ID       : %1\n"
                             "Nom      : %2 %3\n"
                             "Poste    : %4\n"
                             "Tél      : %5\n"
                             "Mail     : %6")
                             .arg(e.id, e.prenom, e.nom, e.poste, e.telephone, e.mail);

    // Appel de notre nouvelle classe QRCodeGenerator
    const QPixmap pm = QRCodeGenerator::generate(data);

    if (pm.isNull()) {
        ui->lblQrImage->setText("Erreur de génération");
        ui->lblQrInfo->clear();
        return;
    }
    ui->lblQrImage->setPixmap(pm.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lblQrInfo->setText(QString("<b>%1 %2</b><br>%3<br>%4<br>%5")
                               .arg(e.prenom, e.nom, e.poste, e.mail, e.telephone));
}

void MainWindow::on_btnSaveQr_clicked()
{
    const QPixmap pm = ui->lblQrImage->pixmap();
    if (pm.isNull()) {
        warning(this, "Aucun QR", "Sélectionnez d'abord un employé.");
        return;
    }
    QString path = QFileDialog::getSaveFileName(this, "Enregistrer le QR code",
                                                "QR_" + ui->txtId->text() + ".png", "PNG (*.png)");
    if (path.isEmpty()) return;
    if (!path.endsWith(".png", Qt::CaseInsensitive)) path += ".png";
    pm.save(path);
    QMessageBox::information(this, "Succès", "QR code enregistré :\n" + path);
}

void MainWindow::on_btnTrierPrix_clicked()
{
    std::sort(m_employes.begin(), m_employes.end(), [this](const auto &a, const auto &b) {
        const int c = QString::compare(a.nom, b.nom, Qt::CaseInsensitive);
        return m_sortAscNom ? c < 0 : c > 0;
    });
    m_sortAscNom = !m_sortAscNom;
    ui->btnTrierPrix->setText(m_sortAscNom ? "↕ Trier par nom" : "↕ Nom décroissant");
    refreshTable();
}

void MainWindow::on_btnTrierDate_clicked()
{
    std::sort(m_employes.begin(), m_employes.end(), [this](const auto &a, const auto &b) {
        const int c = QString::compare(a.poste, b.poste, Qt::CaseInsensitive);
        return m_sortAscPoste ? c < 0 : c > 0;
    });
    m_sortAscPoste = !m_sortAscPoste;
    ui->btnTrierDate->setText(m_sortAscPoste ? "↕ Trier par poste" : "↕ Poste décroissant");
    refreshTable();
}

void MainWindow::on_inputSearch_textChanged(const QString &) { refreshTable(); }
void MainWindow::on_comboFilterType_currentTextChanged(const QString &) { refreshTable(); }

void MainWindow::on_btnExportPdf_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Exporter les employés en PDF", "Employes.pdf", "PDF (*.pdf)");
    if (path.isEmpty()) return;
    if (!path.endsWith(".pdf", Qt::CaseInsensitive)) path += ".pdf";
    const auto list = currentFilteredList();
    QString html = "<h2 style='text-align:center'>Pawché - Employés</h2><p>";
    html += QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + " · " + QString::number(list.size()) + " employé(s)</p>";
    html += "<table width='100%' border='1' cellspacing='0' cellpadding='6'>"
            "<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Téléphone</th><th>Mail</th></tr>";
    for (const auto &e : list)
        html += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
                    .arg(e.id.toHtmlEscaped(), e.nom.toHtmlEscaped(), e.prenom.toHtmlEscaped(),
                         e.telephone.toHtmlEscaped(), e.mail.toHtmlEscaped());
    QTextDocument doc; doc.setHtml(html + "</table>");
    QPdfWriter writer(path); writer.setPageSize(QPageSize(QPageSize::A4)); writer.setResolution(300); doc.print(&writer);
    QMessageBox::information(this, "Exportation réussie", "PDF créé :\n" + path);
}