#include "Petcarecenter.h"

#include <QDateTime>
#include <QFileDialog>
#include <QHeaderView>
#include <QList>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QPushButton>
#include <QRegularExpression>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>

#include "ui_Petcarecenter.h"

namespace {
Animal::Health healthFromStringValue(const QString &value)
{
    if (value.compare("Urgent", Qt::CaseInsensitive) == 0) return Animal::Health::Urgent;
    if (value.compare("En soin", Qt::CaseInsensitive) == 0) return Animal::Health::EnSoin;
    return Animal::Health::Sain;
}

bool isNameValid(const QString &value)
{
    static const QRegularExpression expression(QStringLiteral("^[\\p{L}]+(?:[ '-][\\p{L}]+)*$"));
    return expression.match(value).hasMatch();
}
}

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
    const Animal::Health sante = static_cast<Animal::Health>(ui->combosante->currentIndex());
    const QDate dateNaissance = QDate::currentDate().addYears(-ui->spinage->value());
    const QString telephone = ui->edittelephone->text().trimmed();

    if (nom.isEmpty()) {
        ui->lblerreur->setText(tr("Veuillez saisir le nom de l'animal."));
        ui->editnom->setFocus();
        return;
    }
    if (!isNameValid(nom)) {
        ui->lblerreur->setText(tr("Le nom de l'animal doit contenir uniquement des lettres."));
        ui->editnom->setFocus();
        return;
    }
    if (proprietaire.isEmpty()) {
        ui->lblerreur->setText(tr("Veuillez saisir le nom du propriétaire."));
        ui->editproprietaire->setFocus();
        return;
    }
    if (!isNameValid(proprietaire)) {
        ui->lblerreur->setText(tr("Le nom du propriétaire doit contenir uniquement des lettres."));
        ui->editproprietaire->setFocus();
        return;
    }
    if (!telephone.isEmpty() && !QRegularExpression(QStringLiteral("^[0-9]{8}$")).match(telephone).hasMatch()) {
        ui->lblerreur->setText(tr("Le numéro de téléphone doit contenir exactement 8 chiffres."));
        ui->edittelephone->setFocus();
        return;
    }
    if (!puce.isEmpty() && !QRegularExpression(QStringLiteral("^[0-9]{15}$")).match(puce).hasMatch()) {
        ui->lblerreur->setText(tr("Le numéro de puce doit contenir exactement 15 chiffres."));
        ui->editpuce->setFocus();
        return;
    }

    const bool isNew = (m_editId == 0);
    Animal a(nom, espece, race, dateNaissance, puce, vaccinal, proprietaire, phoneDigits(), sante);
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

    QSqlQuery q;
    q.prepare("SELECT id_animal, nom, espece, race, date_naissance, puce, vaccinal, nom_proprietaire, TO_CHAR(telephone), etat_sante FROM animaux WHERE id_animal = :id");
    q.bindValue(":id", id);
    if (!q.exec() || !q.next()) return;

    const QDate dateNaissance = q.value(4).toDate();
    const Animal::Health etatSante = healthFromStringValue(q.value(9).toString());
    int age = 0;
    if (dateNaissance.isValid()) {
        age = QDate::currentDate().year() - dateNaissance.year();
        if (QDate::currentDate() < dateNaissance.addYears(age)) {
            --age;
        }
        age = qMax(0, age);
    }

    m_editId = id;
    ui->lbltitreformulaire->setText(tr("Modifier l'animal"));
    ui->editnom->setText(q.value(1).toString());
    ui->comboespece->setCurrentText(q.value(2).toString());
    ui->editrace->setText(q.value(3).toString());
    ui->spinage->setValue(age);
    ui->editpuce->setText(q.value(5).toString());
    ui->combovaccinal->setCurrentText(q.value(6).toString());
    ui->editproprietaire->setText(q.value(7).toString());
    ui->edittelephone->setText(q.value(8).toString());
    ui->combosante->setCurrentIndex(static_cast<int>(etatSante));
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
        const Animal::Health s = healthFromStringValue(etat);

        switch (s) {
        case Animal::Health::Sain:
            ++good;
            break;
        case Animal::Health::EnSoin:
            ++care;
            break;
        case Animal::Health::Urgent:
            ++urgent;
            break;
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
        auto *status = new QTableWidgetItem(Animal::healthText(s));
        status->setForeground(Animal::healthColor(s));
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
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter le carnet de vaccination en PDF"), QStringLiteral("Carnet_Vaccination.pdf"), tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) return;

    struct AnimalRecord {
        QString nom;
        QString espece;
        QString race;
        QString dateNaissance;
        QString puce;
        QString statutVaccinal;
        QString proprietaire;
        QString telephone;
    };

    QList<AnimalRecord> animaux;
    QSqlQuery query;
    if (!query.exec("SELECT nom, espece, race, date_naissance, puce, vaccinal, nom_proprietaire, TO_CHAR(telephone) FROM animaux ORDER BY nom ASC")) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de lire les animaux :\n%1").arg(query.lastError().text()));
        return;
    }
    while (query.next()) {
        const QDate dateNaissance = query.value(3).toDate();
        animaux.append({
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            dateNaissance.isValid() ? dateNaissance.toString("dd/MM/yyyy") : tr("Non renseignée"),
            query.value(4).toString().isEmpty() ? tr("Non renseigné") : query.value(4).toString(),
            query.value(5).toString().isEmpty() ? tr("Inconnu") : query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString()
        });
    }
    if (query.lastError().isValid()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de lire les animaux :\n%1").arg(query.lastError().text()));
        return;
    }
    if (animaux.isEmpty()) {
        QMessageBox::information(this, tr("Carnet de vaccination"), tr("Aucun animal à exporter."));
        return;
    }

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Portrait);
    writer.setResolution(300);

    QPainter p(&writer);
    if (!p.isActive()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'initialiser le document PDF."));
        return;
    }

    const int margin = 170;
    const int contentWidth = writer.width() - 2 * margin;
    const int cellGap = 30;
    const int columnWidth = (contentWidth - 2 * cellGap) / 3;
    const QString generatedAt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm");
    const QFont title("Arial", 28, QFont::Bold);
    const QFont section("Arial", 16, QFont::Bold);
    const QFont label("Arial", 11, QFont::Bold);
    const QFont value("Arial", 13);
    const QFont small("Arial", 10);

    for (int index = 0; index < animaux.size(); ++index) {
        if (index > 0)
            writer.newPage();

        const AnimalRecord &animal = animaux[index];
        p.setPen(QColor("#713923"));
        p.setFont(title);
        p.drawText(QRect(margin, 170, contentWidth, 90), Qt::AlignLeft | Qt::AlignVCenter, tr("Carnet de vaccination"));
        p.setPen(QColor("#666666"));
        p.setFont(small);
        p.drawText(QRect(margin, 255, contentWidth, 50), Qt::AlignLeft | Qt::AlignVCenter,
                   tr("Pawché  •  Généré le %1").arg(generatedAt));

        int y = 390;
        p.setPen(Qt::NoPen);
        p.setBrush(QColor("#F8E5DF"));
        p.drawRoundedRect(QRect(margin, y, contentWidth, 72), 8, 8);
        p.setPen(QColor("#713923"));
        p.setFont(section);
        p.drawText(QRect(margin + 24, y, contentWidth - 48, 72), Qt::AlignVCenter, tr("Identification de l'animal"));

        const auto drawField = [&p, &label, &value](const QString &caption, const QString &text, int x, int top, int width) {
            p.setPen(QColor("#777777"));
            p.setFont(label);
            p.drawText(QRect(x, top, width, 36), Qt::AlignLeft | Qt::AlignVCenter, caption);
            p.setPen(QColor("#222222"));
            p.setFont(value);
            p.drawText(QRect(x, top + 36, width, 54), Qt::AlignLeft | Qt::AlignVCenter, text);
        };

        const int firstColumn = margin;
        const int secondColumn = margin + columnWidth + cellGap;
        const int thirdColumn = margin + 2 * (columnWidth + cellGap);
        const int fieldsTop = y + 108;
        drawField(tr("Nom"), animal.nom, firstColumn, fieldsTop, columnWidth);
        drawField(tr("Espèce"), animal.espece, secondColumn, fieldsTop, columnWidth);
        drawField(tr("Race"), animal.race, thirdColumn, fieldsTop, columnWidth);
        drawField(tr("Date de naissance"), animal.dateNaissance, firstColumn, fieldsTop + 120, columnWidth);
        drawField(tr("N° de puce"), animal.puce, secondColumn, fieldsTop + 120, columnWidth);
        drawField(tr("Statut vaccinal enregistré"), animal.statutVaccinal, thirdColumn, fieldsTop + 120, columnWidth);
        drawField(tr("Propriétaire"), animal.proprietaire, firstColumn, fieldsTop + 240, columnWidth * 2 + cellGap);
        drawField(tr("Téléphone"), animal.telephone, thirdColumn, fieldsTop + 240, columnWidth);

        y = fieldsTop + 370;
        p.setPen(QColor("#713923"));
        p.setFont(section);
        p.drawText(QRect(margin, y, contentWidth, 60), Qt::AlignLeft | Qt::AlignVCenter, tr("Historique des vaccinations"));
        y += 70;
        p.setPen(QColor("#555555"));
        p.setFont(small);
        p.drawText(QRect(margin, y, contentWidth, 48), Qt::AlignLeft | Qt::AlignVCenter,
                   tr("Aucun historique détaillé n'est enregistré. Les vaccinations peuvent être consignées ci-dessous."));
        y += 62;

        const int rowHeight = 200;
        const int widths[] = {
            contentWidth * 42 / 100,
            contentWidth * 19 / 100,
            contentWidth * 19 / 100,
            contentWidth - (contentWidth * 42 / 100) - 2 * (contentWidth * 19 / 100)
        };
        const QString headers[] = {tr("Vaccin"), tr("Date"), tr("Prochain rappel"), tr("Vétérinaire / signature")};
        p.setPen(Qt::NoPen);
        p.setBrush(QColor("#F8E5DF"));
        p.drawRect(margin, y, contentWidth, 76);
        p.setPen(QColor("#713923"));
        p.setFont(label);
        int x = margin;
        for (int column = 0; column < 4; ++column) {
            p.drawText(QRect(x + 12, y, widths[column] - 24, 76), Qt::AlignLeft | Qt::AlignVCenter, headers[column]);
            x += widths[column];
        }
        y += 76;

        p.setPen(QColor("#D9C8BE"));
        p.setBrush(Qt::NoBrush);
        for (int row = 0; row < 8; ++row) {
            p.drawRect(margin, y, contentWidth, rowHeight);
            x = margin;
            for (int column = 0; column < 4; ++column) {
                if (column > 0)
                    p.drawLine(x, y, x, y + rowHeight);
                x += widths[column];
            }
            y += rowHeight;
        }

        p.setPen(QColor("#777777"));
        p.setFont(small);
        p.drawText(QRect(margin, writer.height() - 200, contentWidth, 48), Qt::AlignLeft | Qt::AlignVCenter,
                   tr("Ce document ne remplace pas le carnet vétérinaire officiel."));
    }

    p.end();
    QMessageBox::information(this, tr("Succès"), tr("Le carnet de vaccination a été exporté avec succès en PDF :\n%1").arg(fileName));
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
    const QString value = ui->edittelephone->text().trimmed();
    return value.isEmpty() ? QStringLiteral("0") : value;
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
