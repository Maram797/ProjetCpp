#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPushButton>
#include <QSettings>
#include <QStyle>
#include <QTextDocument>
#include <algorithm>

namespace {
QString normalized(const QString &value)
{
    return value.trimmed().toLower();
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_sortAscNom(true),
      m_sortAscPrenom(true)
{
    ui->setupUi(this);

    const QList<QPushButton *> navButtons{
        ui->btnNavAnimaux, ui->btnNavCommandes, ui->btnNavSoins,
        ui->btnNavProduits, ui->btnNavPaiements
    };
    for (QPushButton *button : navButtons) {
        button->setCursor(Qt::PointingHandCursor);
        button->setProperty("active", button == ui->btnNavCommandes);
        connect(button, &QPushButton::clicked, this, [navButtons, button]() {
            for (QPushButton *navButton : navButtons) {
                navButton->setProperty("active", navButton == button);
                navButton->style()->unpolish(navButton);
                navButton->style()->polish(navButton);
                navButton->update();
            }
        });
    }

    setWindowTitle(QStringLiteral("Pawché - Gestion des fournisseurs"));
    ui->comboFilterType->setItemText(0, QStringLiteral("Tous les fournisseurs"));
    ui->btnTrierPrix->setText(QStringLiteral("↕ Trier par nom"));
    ui->btnTrierDate->setText(QStringLiteral("↕ Trier par prénom"));
    ui->lblAlertHeading->setText(QStringLiteral("Fournisseurs enregistrés"));
    ui->lblAlertDesc->setText(QStringLiteral("Aucun fournisseur enregistré"));
    ui->lblTotalMontant->setText(QStringLiteral("Avec e-mail : 0"));

    ui->tableCommandes->setColumnCount(5);
    ui->tableCommandes->setHorizontalHeaderLabels({
        QStringLiteral("ID fournisseur"), QStringLiteral("Nom"),
        QStringLiteral("Prénom"), QStringLiteral("Téléphone"), QStringLiteral("Mail")
    });
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    loadFournisseurs();
    refreshTable();
    updateStatistics();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFournisseurs()
{
    QSettings settings(QStringLiteral("Pawche"), QStringLiteral("GestionFournisseurs"));
    const int count = settings.beginReadArray(QStringLiteral("fournisseurs"));
    for (int i = 0; i < count; ++i) {
        settings.setArrayIndex(i);
        Fournisseur f;
        f.id = settings.value(QStringLiteral("id")).toString();
        f.nom = settings.value(QStringLiteral("nom")).toString();
        f.prenom = settings.value(QStringLiteral("prenom")).toString();
        f.telephone = settings.value(QStringLiteral("telephone")).toString();
        f.mail = settings.value(QStringLiteral("mail")).toString();
        if (!f.id.isEmpty())
            m_fournisseurs.append(f);
    }
    settings.endArray();
}

void MainWindow::saveFournisseurs() const
{
    QSettings settings(QStringLiteral("Pawche"), QStringLiteral("GestionFournisseurs"));
    settings.beginWriteArray(QStringLiteral("fournisseurs"));
    for (int i = 0; i < m_fournisseurs.size(); ++i) {
        settings.setArrayIndex(i);
        const Fournisseur &f = m_fournisseurs.at(i);
        settings.setValue(QStringLiteral("id"), f.id);
        settings.setValue(QStringLiteral("nom"), f.nom);
        settings.setValue(QStringLiteral("prenom"), f.prenom);
        settings.setValue(QStringLiteral("telephone"), f.telephone);
        settings.setValue(QStringLiteral("mail"), f.mail);
    }
    settings.endArray();
    settings.sync();
}

int MainWindow::fournisseurIndex(const QString &id) const
{
    for (int i = 0; i < m_fournisseurs.size(); ++i) {
        if (m_fournisseurs.at(i).id.compare(id, Qt::CaseInsensitive) == 0)
            return i;
    }
    return -1;
}

Fournisseur MainWindow::fournisseurFromForm() const
{
    return {ui->txtId->text().trimmed(), ui->lineEdit->text().trimmed(),
            ui->lineEdit_2->text().trimmed(), ui->lineEdit_3->text().trimmed(),
            ui->lineEdit_4->text().trimmed()};
}

bool MainWindow::formIsValid()
{
    const Fournisseur f = fournisseurFromForm();
    if (f.id.isEmpty() || f.nom.isEmpty() || f.prenom.isEmpty()
        || f.telephone.isEmpty() || f.mail.isEmpty()) {
        QMessageBox::warning(this, QStringLiteral("Champs requis"),
                             QStringLiteral("Remplissez tous les champs du fournisseur."));
        return false;
    }
    if (!f.mail.contains(QLatin1Char('@')) || !f.mail.section(QLatin1Char('@'), 1).contains(QLatin1Char('.'))) {
        QMessageBox::warning(this, QStringLiteral("E-mail invalide"),
                             QStringLiteral("Saisissez une adresse e-mail valide."));
        ui->lineEdit_4->setFocus();
        return false;
    }
    return true;
}

QList<Fournisseur> MainWindow::currentFilteredList() const
{
    const QString query = normalized(ui->inputSearch->text());
    const QString filter = ui->comboFilterType->currentText();
    QList<Fournisseur> result;
    for (const Fournisseur &f : m_fournisseurs) {
        const QString mail = normalized(f.mail);
        bool matchesProvider = true;
        if (filter == QStringLiteral("Gmail")) matchesProvider = mail.endsWith(QStringLiteral("@gmail.com"));
        else if (filter == QStringLiteral("Outlook")) matchesProvider = mail.endsWith(QStringLiteral("@outlook.com")) || mail.endsWith(QStringLiteral("@hotmail.com"));
        else if (filter == QStringLiteral("Yahoo")) matchesProvider = mail.endsWith(QStringLiteral("@yahoo.com"));
        else if (filter == QStringLiteral("Autres domaines"))
            matchesProvider = !mail.endsWith(QStringLiteral("@gmail.com"))
                && !mail.endsWith(QStringLiteral("@outlook.com"))
                && !mail.endsWith(QStringLiteral("@hotmail.com"))
                && !mail.endsWith(QStringLiteral("@yahoo.com"));

        const bool matchesQuery = query.isEmpty()
            || normalized(f.id).contains(query) || normalized(f.nom).contains(query)
            || normalized(f.prenom).contains(query) || normalized(f.telephone).contains(query)
            || mail.contains(query);
        if (matchesProvider && matchesQuery)
            result.append(f);
    }
    return result;
}

void MainWindow::refreshTable()
{
    const QList<Fournisseur> list = currentFilteredList();
    ui->tableCommandes->setRowCount(0);
    for (const Fournisseur &f : list) {
        const int row = ui->tableCommandes->rowCount();
        ui->tableCommandes->insertRow(row);
        const QStringList values{f.id, f.nom, f.prenom, f.telephone, f.mail};
        for (int column = 0; column < values.size(); ++column) {
            auto *item = new QTableWidgetItem(values.at(column));
            if (column < 4)
                item->setTextAlignment(Qt::AlignCenter);
            ui->tableCommandes->setItem(row, column, item);
        }
    }
}

void MainWindow::updateStatistics()
{
    QMap<QString, int> stats;
    for (const Fournisseur &f : m_fournisseurs) {
        const QString domain = f.mail.section(QLatin1Char('@'), 1).toLower();
        stats[domain.isEmpty() ? QStringLiteral("Sans e-mail") : domain]++;
    }
    ui->widgetCurve->updateData(stats);
    ui->lblAlertBadge->setText(QString::number(m_fournisseurs.size()));
    ui->lblAlertDesc->setText(m_fournisseurs.size() == 1
        ? QStringLiteral("fournisseur enregistré")
        : QStringLiteral("fournisseurs enregistrés"));
    const int withEmail = std::count_if(m_fournisseurs.cbegin(), m_fournisseurs.cend(),
                                        [](const Fournisseur &f) { return !f.mail.isEmpty(); });
    ui->lblTotalMontant->setText(QStringLiteral("Avec e-mail : %1").arg(withEmail));
}

void MainWindow::clearForm()
{
    ui->txtId->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->txtId->setEnabled(true);
    ui->txtId->setFocus();
    ui->tableCommandes->clearSelection();
}

void MainWindow::on_btnAjouter_clicked()
{
    if (!formIsValid()) return;
    const Fournisseur f = fournisseurFromForm();
    if (fournisseurIndex(f.id) >= 0) {
        QMessageBox::warning(this, QStringLiteral("Identifiant déjà utilisé"),
                             QStringLiteral("Un fournisseur existe déjà avec cet identifiant."));
        return;
    }
    m_fournisseurs.append(f);
    saveFournisseurs();
    refreshTable();
    updateStatistics();
    clearForm();
}

void MainWindow::on_btnModifier_clicked()
{
    const int row = ui->tableCommandes->currentRow();
    if (row < 0 || !ui->tableCommandes->item(row, 0)) {
        QMessageBox::warning(this, QStringLiteral("Sélection requise"),
                             QStringLiteral("Sélectionnez un fournisseur à modifier."));
        return;
    }
    if (!formIsValid()) return;
    const QString oldId = ui->tableCommandes->item(row, 0)->text();
    const Fournisseur f = fournisseurFromForm();
    const int index = fournisseurIndex(oldId);
    if (index < 0) return;
    const int duplicateIndex = fournisseurIndex(f.id);
    if (duplicateIndex >= 0 && duplicateIndex != index) {
        QMessageBox::warning(this, QStringLiteral("Identifiant déjà utilisé"),
                             QStringLiteral("Un autre fournisseur possède cet identifiant."));
        return;
    }
    m_fournisseurs[index] = f;
    saveFournisseurs();
    refreshTable();
    updateStatistics();
    clearForm();
}

void MainWindow::on_btnSupprimer_clicked()
{
    const int row = ui->tableCommandes->currentRow();
    if (row < 0 || !ui->tableCommandes->item(row, 0)) {
        QMessageBox::warning(this, QStringLiteral("Sélection requise"),
                             QStringLiteral("Sélectionnez un fournisseur à supprimer."));
        return;
    }
    const QString id = ui->tableCommandes->item(row, 0)->text();
    const auto answer = QMessageBox::question(this, QStringLiteral("Confirmation"),
        QStringLiteral("Supprimer le fournisseur %1 ?").arg(id), QMessageBox::Yes | QMessageBox::No);
    if (answer != QMessageBox::Yes) return;
    const int index = fournisseurIndex(id);
    if (index >= 0) m_fournisseurs.removeAt(index);
    saveFournisseurs();
    refreshTable();
    updateStatistics();
    clearForm();
}

void MainWindow::on_btnVider_clicked()
{
    clearForm();
}

void MainWindow::on_tableCommandes_cellClicked(int row, int)
{
    if (row < 0 || !ui->tableCommandes->item(row, 0)) return;
    const int index = fournisseurIndex(ui->tableCommandes->item(row, 0)->text());
    if (index < 0) return;
    const Fournisseur &f = m_fournisseurs.at(index);
    ui->txtId->setText(f.id);
    ui->txtId->setEnabled(false);
    ui->lineEdit->setText(f.nom);
    ui->lineEdit_2->setText(f.prenom);
    ui->lineEdit_3->setText(f.telephone);
    ui->lineEdit_4->setText(f.mail);
}

void MainWindow::on_btnTrierPrix_clicked()
{
    std::sort(m_fournisseurs.begin(), m_fournisseurs.end(), [this](const Fournisseur &a, const Fournisseur &b) {
        const int cmp = QString::compare(a.nom, b.nom, Qt::CaseInsensitive);
        return m_sortAscNom ? cmp < 0 : cmp > 0;
    });
    m_sortAscNom = !m_sortAscNom;
    ui->btnTrierPrix->setText(m_sortAscNom ? QStringLiteral("↕ Trier par nom") : QStringLiteral("↕ Nom décroissant"));
    refreshTable();
}

void MainWindow::on_btnTrierDate_clicked()
{
    std::sort(m_fournisseurs.begin(), m_fournisseurs.end(), [this](const Fournisseur &a, const Fournisseur &b) {
        const int cmp = QString::compare(a.prenom, b.prenom, Qt::CaseInsensitive);
        return m_sortAscPrenom ? cmp < 0 : cmp > 0;
    });
    m_sortAscPrenom = !m_sortAscPrenom;
    ui->btnTrierDate->setText(m_sortAscPrenom ? QStringLiteral("↕ Trier par prénom") : QStringLiteral("↕ Prénom décroissant"));
    refreshTable();
}

void MainWindow::on_inputSearch_textChanged(const QString &)
{
    refreshTable();
}

void MainWindow::on_comboFilterType_currentTextChanged(const QString &)
{
    refreshTable();
}

void MainWindow::on_btnExportPdf_clicked()
{
    const QString path = QFileDialog::getSaveFileName(this, QStringLiteral("Exporter les fournisseurs en PDF"),
        QStringLiteral("Fournisseurs.pdf"), QStringLiteral("Fichiers PDF (*.pdf)"));
    if (path.isEmpty()) return;
    const QString pdfPath = path.endsWith(QStringLiteral(".pdf"), Qt::CaseInsensitive) ? path : path + QStringLiteral(".pdf");
    const QList<Fournisseur> list = currentFilteredList();

    QString html = QStringLiteral(
        "<!DOCTYPE html><html><head><meta charset='utf-8'><style>"
        "body{font-family:Arial,sans-serif;color:#3D2619;margin:30px}"
        "h1{text-align:center;color:#5C3826}p{text-align:center;color:#7D6658}"
        "table{width:100%;border-collapse:collapse;margin-top:24px}"
        "th{background:#5C3826;color:white;padding:10px}"
        "td{border:1px solid #EFE6DF;padding:8px;text-align:center}"
        "tr:nth-child(even){background:#FAF5F0}</style></head><body>");
    html += QStringLiteral("<h1>Pawché - Liste des fournisseurs</h1><p>Exporté le %1 · %2 fournisseur(s)</p>")
        .arg(QDateTime::currentDateTime().toString(QStringLiteral("dd/MM/yyyy HH:mm"))).arg(list.size());
    html += QStringLiteral("<table><thead><tr><th>ID fournisseur</th><th>Nom</th><th>Prénom</th><th>Téléphone</th><th>Mail</th></tr></thead><tbody>");
    for (const Fournisseur &f : list) {
        html += QStringLiteral("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
            .arg(f.id.toHtmlEscaped(), f.nom.toHtmlEscaped(), f.prenom.toHtmlEscaped(),
                 f.telephone.toHtmlEscaped(), f.mail.toHtmlEscaped());
    }
    html += QStringLiteral("</tbody></table></body></html>");
    QTextDocument document;
    document.setHtml(html);
    QPdfWriter writer(pdfPath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    document.print(&writer);
    QMessageBox::information(this, QStringLiteral("Exportation réussie"),
        QStringLiteral("Le fichier PDF a été généré :\n%1").arg(pdfPath));
}
