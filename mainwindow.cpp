#include "mainwindow.h"

#include <QFileDialog>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QPushButton>
#include <QRegularExpression>
#include <QTableWidget>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cadreformulaire->hide();
    ui->tableanimaux->verticalHeader()->hide();
    ui->tableanimaux->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableanimaux->setShowGrid(false);

    QPixmap logo(":/logo.jpg");
    if (logo.isNull()) logo.load("logo.jpg");
    if (!logo.isNull()) {
        ui->lblmarque->setPixmap(logo.scaled(172, 114, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->lblmarque->setAlignment(Qt::AlignCenter);
    }

    connect(ui->editrecherche, &QLineEdit::textChanged, this, &MainWindow::on_editrecherche_textChanged);
    connect(ui->editfiltre, &QLineEdit::textChanged, this, &MainWindow::on_editfiltre_textChanged);
    connect(ui->btntous, &QPushButton::clicked, this, &MainWindow::actualiserAffichage);
    connect(ui->btnchiens, &QPushButton::clicked, this, &MainWindow::actualiserAffichage);
    connect(ui->btnchats, &QPushButton::clicked, this, &MainWindow::actualiserAffichage);
    connect(ui->btnnouvelanimal, &QPushButton::clicked, this, &MainWindow::on_btnnouvelanimal_clicked);
    connect(ui->btnannuler, &QPushButton::clicked, this, &MainWindow::on_btnannuler_clicked);
    connect(ui->btnajouter, &QPushButton::clicked, this, &MainWindow::on_pushbutton_ajouter_clicked);
    connect(ui->tableanimaux, &QTableWidget::itemSelectionChanged, this, &MainWindow::on_tableanimaux_selectionChanged);
    connect(ui->btnsupprimer, &QPushButton::clicked, this, &MainWindow::on_pushbutton_supprimer_clicked);
    connect(ui->btnmodifier, &QPushButton::clicked, this, &MainWindow::on_btnmodifier_clicked);
    connect(ui->btntrierdate, &QPushButton::clicked, this, &MainWindow::on_pushbutton_trierdate_clicked);
    connect(ui->btnexporterpdf, &QPushButton::clicked, this, &MainWindow::on_pushbutton_exporterpdf_clicked);
    connect(ui->btnsync, &QPushButton::clicked, this, &QWidget::close);

    if (!Animal::ensureTable())
        QMessageBox::warning(this, tr("Base de données"), tr("Table ANIMAUX indisponible ou en cours d'initialisation."));

    actualiserAffichage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushbutton_ajouter_clicked()
{
    const QString nom = ui->editnom->text().trimmed();
    const QString race = ui->editrace->text().trimmed();
    const QString proprietaire = ui->editproprietaire->text().trimmed();
    const QString puce = ui->editpuce->text().trimmed();
    const QString espece = ui->comboespece->currentText();
    const QString vaccinal = ui->combovaccinal->currentText();
    const Health sante = static_cast<Health>(ui->combosante->currentIndex());
    const QDate dateNaissance = QDate::currentDate().addYears(-ui->spinage->value());

    if (nom.isEmpty()) {
        ui->lblerreur->setText(tr("Veuillez saisir le nom de l'animal."));
        ui->editnom->setFocus();
        return;
    }
    if (proprietaire.isEmpty()) {
        ui->lblerreur->setText(tr("Veuillez saisir le nom du propriétaire."));
        ui->editproprietaire->setFocus();
        return;
    }

    const bool isNew = (m_editId == 0);
    Animal a(m_editId, nom, espece, race, dateNaissance, puce, vaccinal, proprietaire, phoneDigits(), sante);
    if ((isNew ? a.ajouter() : a.modifier(m_editId))) {
        actualiserAffichage();
        clearForm();
        showList();
        QMessageBox::information(nullptr, tr("OK"), (isNew ? tr("Ajout effectué\n") : tr("Modification effectuée\n")) + tr("Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, tr("Not OK"), (isNew ? tr("Ajout non effectué.\n") : tr("Modification non effectuée.\n")) + tr("Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushbutton_supprimer_clicked()
{
    const int id = selectedId();
    if (id <= 0) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un animal à supprimer."));
        return;
    }
    if (Etmp.supprimer(id)) {
        actualiserAffichage();
        QMessageBox::information(nullptr, tr("OK"), tr("Suppression effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, tr("Not OK"), tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushbutton_trierdate_clicked()
{
    m_sortAsc = !m_sortAsc;
    auto *model = Etmp.trierParDateNaissance(m_sortAsc);
    chargerTableDepuisModele(model);
    delete model;
}

void MainWindow::on_pushbutton_exporterpdf_clicked()
{
    exporterEnPdf();
}

void MainWindow::on_btnmodifier_clicked()
{
    const int id = selectedId();
    if (id <= 0) return;

    Animal a = Animal::trouverParId(id);
    if (a.getId() <= 0) return;

    m_editId = a.getId();
    ui->lbltitreformulaire->setText(tr("Modifier l'animal"));
    ui->editnom->setText(a.getNom());
    ui->comboespece->setCurrentText(a.getEspece());
    ui->editrace->setText(a.getRace());
    ui->spinage->setValue(a.getAge());
    ui->editpuce->setText(a.getPuce());
    ui->combovaccinal->setCurrentText(a.getVaccinal());
    ui->editproprietaire->setText(a.getProprietaire());
    ui->edittelephone->setText(a.getTelephone());
    ui->combosante->setCurrentIndex(static_cast<int>(a.getSante()));
    ui->pagescentre->setCurrentWidget(ui->pageliste);
    ui->cadreformulaire->show();
    ui->editnom->setFocus();
}

void MainWindow::on_btnnouvelanimal_clicked()
{
    clearForm();
    m_editId = 0;
    ui->lbltitreformulaire->setText(tr("Nouvel animal"));
    ui->pagescentre->setCurrentWidget(ui->pageliste);
    ui->cadreformulaire->show();
    ui->editnom->setFocus();
}

void MainWindow::on_btnannuler_clicked()
{
    clearForm();
    showList();
}

void MainWindow::on_tableanimaux_selectionChanged()
{
    const bool selected = selectedId() > 0;
    ui->btnmodifier->setEnabled(selected);
    ui->btnsupprimer->setEnabled(selected);
}

void MainWindow::on_editrecherche_textChanged()
{
    actualiserAffichage();
}

void MainWindow::on_editfiltre_textChanged()
{
    actualiserAffichage();
}

void MainWindow::actualiserAffichage()
{
    auto *model = Etmp.afficher();
    chargerTableDepuisModele(model);
    delete model;
}

void MainWindow::chargerTableDepuisModele(QSqlQueryModel *model)
{
    if (!model) return;

    const QString critere = filterText();
    int good = 0, care = 0, urgent = 0, total = model->rowCount(), matched = 0;
    ui->tableanimaux->setRowCount(0);

    for (int i = 0; i < total; ++i) {
        const int id = model->index(i, 0).data().toInt();
        const QString nom = model->index(i, 1).data().toString();
        const QString espece = model->index(i, 2).data().toString();
        const QString race = model->index(i, 3).data().toString();
        const int age = model->index(i, 5).data().toInt();
        const QString puce = model->index(i, 6).data().toString();
        const QString proprietaire = model->index(i, 8).data().toString();
        const QString telephone = model->index(i, 9).data().toString();
        const QString etat = model->index(i, 10).data().toString();

        Health s = Health::Sain;
        if (etat.compare("Urgent", Qt::CaseInsensitive) == 0) {
            s = Health::Urgent;
            ++urgent;
        } else if (etat.compare("En soin", Qt::CaseInsensitive) == 0) {
            s = Health::EnSoin;
            ++care;
        } else {
            ++good;
        }

        const bool matchSpecies = ui->btntous->isChecked() || (ui->btnchiens->isChecked() && espece == "Chien") || (ui->btnchats->isChecked() && espece == "Chat");
        const bool matchText = critere.isEmpty() || nom.contains(critere, Qt::CaseInsensitive) || espece.contains(critere, Qt::CaseInsensitive) || race.contains(critere, Qt::CaseInsensitive) || proprietaire.contains(critere, Qt::CaseInsensitive) || puce.contains(critere, Qt::CaseInsensitive);
        if (!(matchSpecies && matchText)) continue;

        ++matched;
        const int row = ui->tableanimaux->rowCount();
        ui->tableanimaux->insertRow(row);

        auto *itemNom = new QTableWidgetItem(QStringLiteral("%1  •  %2").arg(nom, espece));
        itemNom->setData(Qt::UserRole, id);
        ui->tableanimaux->setItem(row, 0, itemNom);
        ui->tableanimaux->setItem(row, 1, new QTableWidgetItem(ageText(age)));
        ui->tableanimaux->setItem(row, 2, new QTableWidgetItem(proprietaire));
        ui->tableanimaux->setItem(row, 3, new QTableWidgetItem(telephone));
        auto *status = new QTableWidgetItem(healthText(s));
        status->setForeground(healthColor(s));
        ui->tableanimaux->setItem(row, 4, status);
    }

    ui->barresains->setValue(total ? qRound(100.0 * good / total) : 0);
    ui->barreensoin->setValue(total ? qRound(100.0 * care / total) : 0);
    ui->barreurgent->setValue(total ? qRound(100.0 * urgent / total) : 0);
    ui->lblcompte->setText(QStringLiteral("%1 sur %2 animaux").arg(matched).arg(total));
    on_tableanimaux_selectionChanged();
}

void MainWindow::exporterEnPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter la table en PDF"), QStringLiteral("Liste_Animaux.pdf"), tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Landscape);
    writer.setResolution(300);

    QPainter p(&writer);
    if (!p.isActive()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'initialiser le document PDF."));
        return;
    }

    const int margin = 100, rowHeight = 60;
    int y = margin;
    QFont title("Arial", 16, QFont::Bold), sub("Arial", 9), head("Arial", 10, QFont::Bold), rowFont("Arial", 9);
    p.setFont(title); p.setPen(QColor("#713923")); p.drawText(margin, y, tr("Pawché - Registre des Animaux")); y += 60;
    p.setFont(sub); p.setPen(QColor("#555555")); p.drawText(margin, y, tr("Document généré le %1").arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm"))); y += 80;

    const int widths[5] = {650, 250, 500, 400, 300};
    const QString heads[5] = {tr("Animal & Espèce"), tr("Âge"), tr("Propriétaire"), tr("Téléphone"), tr("Statut")};
    p.setPen(Qt::NoPen); p.setBrush(QColor("#F8E5DF")); p.drawRect(margin, y, 2100, rowHeight);
    p.setPen(QColor("#713923")); p.setFont(head); int x = margin;
    for (int c = 0; c < 5; ++c) {
        p.drawText(x + 10, y + 40, heads[c]);
        x += widths[c];
    }
    y += rowHeight; p.setFont(rowFont);

    for (int r = 0; r < ui->tableanimaux->rowCount(); ++r) {
        if (y > 2800) {
            writer.newPage();
            y = margin;
        }
        if (r % 2 == 1) {
            p.setPen(Qt::NoPen);
            p.setBrush(QColor("#FAF5F0"));
            p.drawRect(margin, y, 2100, rowHeight);
        }
        x = margin;
        for (int c = 0; c < 5; ++c) {
            QTableWidgetItem *item = ui->tableanimaux->item(r, c);
            const QString text = item ? item->text() : QString();
            p.setPen(c == 4 && item ? item->foreground().color() : QColor("#222222"));
            p.drawText(x + 10, y + 40, text);
            x += widths[c];
        }
        p.setPen(QColor("#E8D8D0"));
        p.drawLine(margin, y + rowHeight, margin + 2100, y + rowHeight);
        y += rowHeight;
    }

    p.end();
    QMessageBox::information(this, tr("Succès"), tr("La liste a été exportée avec succès en PDF:\n%1").arg(fileName));
}

int MainWindow::selectedId() const
{
    const int row = ui->tableanimaux->currentRow();
    return row >= 0 && ui->tableanimaux->item(row, 0) ? ui->tableanimaux->item(row, 0)->data(Qt::UserRole).toInt() : 0;
}

QString MainWindow::filterText() const
{
    return (ui->editrecherche->text() + ' ' + ui->editfiltre->text()).trimmed();
}

QString MainWindow::phoneDigits() const
{
    QString v = ui->edittelephone->text();
    v.remove(QRegularExpression("[^0-9]"));
    return v.isEmpty() ? QStringLiteral("0") : v;
}

void MainWindow::showList()
{
    ui->pagescentre->setCurrentWidget(ui->pageliste);
    ui->cadreformulaire->hide();
}

void MainWindow::clearForm()
{
    ui->editnom->clear();
    ui->editrace->clear();
    ui->editpuce->clear();
    ui->editproprietaire->clear();
    ui->edittelephone->clear();
    ui->spinage->setValue(0);
    ui->comboespece->setCurrentIndex(0);
    ui->combovaccinal->setCurrentIndex(0);
    ui->combosante->setCurrentIndex(0);
    ui->lblerreur->clear();
}
