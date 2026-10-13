#include <QApplication>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidget>
#include <QTextStream>
#include <QRegularExpression>
#include <algorithm>

#include "animal.h"
#include "connection.h"
#include "ui_mainwindow.h"

class MainWindow final : public QMainWindow {
public:
    MainWindow() : ui(new Ui::MainWindow) {
        ui->setupUi(this);
        ui->cadreformulaire->hide();
        ui->tableanimaux->verticalHeader()->hide();
        ui->tableanimaux->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableanimaux->setShowGrid(false);
        connect(ui->editrecherche, &QLineEdit::textChanged, this, [this] { refresh(); });
        connect(ui->editfiltre, &QLineEdit::textChanged, this, [this] { refresh(); });
        connect(ui->btntous, &QPushButton::clicked, this, [this] { refresh(); });
        connect(ui->btnchiens, &QPushButton::clicked, this, [this] { refresh(); });
        connect(ui->btnchats, &QPushButton::clicked, this, [this] { refresh(); });
        connect(ui->btnnouvelanimal, &QPushButton::clicked, this, [this] { showForm(); });
        connect(ui->btnannuler, &QPushButton::clicked, this, [this] { clearForm(); showList(); });
        connect(ui->btnajouter, &QPushButton::clicked, this, [this] { saveAnimal(); });
        connect(ui->tableanimaux, &QTableWidget::itemSelectionChanged, this, [this] { updateActions(); });
        connect(ui->btnsupprimer, &QPushButton::clicked, this, [this] { deleteSelected(); });
        connect(ui->btnmodifier, &QPushButton::clicked, this, [this] { editSelected(); });
        if (!ensureAnimalsTable()) QMessageBox::warning(this, "Base de donnees", "Table ANIMAUX indisponible.\n" + m_databaseError);
        refresh();
    }
    ~MainWindow() override { delete ui; }

private:
    bool ensureAnimalsTable() {
        QSqlQuery query;
        if (query.exec("CREATE TABLE animaux (id_animal NUMBER PRIMARY KEY, nom VARCHAR2(100) NOT NULL, race VARCHAR2(100) NOT NULL, sexe VARCHAR2(30) NOT NULL, date_naissance DATE NOT NULL, allergies VARCHAR2(200) NOT NULL, etat_sante VARCHAR2(30) NOT NULL, nom_proprietaire VARCHAR2(100) NOT NULL, telephone NUMBER NOT NULL, email VARCHAR2(100) NOT NULL, adresse VARCHAR2(200) NOT NULL, espece VARCHAR2(30), puce VARCHAR2(30), vaccinal VARCHAR2(30))")) return true;
        const QString error = query.lastError().text();
        if (error.contains("ORA-00955", Qt::CaseInsensitive) || error.contains("already exists", Qt::CaseInsensitive)) {
            const auto addColumn = [this](const QString &definition) {
                QSqlQuery alter;
                if (alter.exec("ALTER TABLE animaux ADD (" + definition + ')')) return true;
                const QString alterError = alter.lastError().text();
                if (alterError.contains("ORA-01430", Qt::CaseInsensitive) || alterError.contains("already exists", Qt::CaseInsensitive)) return true;
                m_databaseError = alterError;
                return false;
            };
            return addColumn("espece VARCHAR2(30)") && addColumn("puce VARCHAR2(30)") && addColumn("vaccinal VARCHAR2(30)");
        }
        m_databaseError = error; return false;
    }
    QList<Animal> loadAnimals() {
        QList<Animal> animals; QSqlQuery query;
        if (!query.exec("SELECT id_animal, nom, espece, race, TRUNC(MONTHS_BETWEEN(SYSDATE, date_naissance) / 12), puce, vaccinal, nom_proprietaire, TO_CHAR(telephone), etat_sante FROM animaux ORDER BY nom")) { m_databaseError = query.lastError().text(); return animals; }
        while (query.next()) {
            Animal a; a.id = query.value(0).toInt(); a.nom = query.value(1).toString(); a.espece = query.value(2).toString(); a.race = query.value(3).toString(); a.age = query.value(4).toInt(); a.puce = query.value(5).toString(); a.vaccinal = query.value(6).toString(); a.proprietaire = query.value(7).toString(); a.telephone = query.value(8).toString(); a.sante = healthFromDatabase(query.value(9).toString()); animals.append(a);
        }
        return animals;
    }
    QString filterText() const { return (ui->editrecherche->text() + ' ' + ui->editfiltre->text()).trimmed(); }
    Health healthFromDatabase(const QString &value) const {
        if (value.compare("Urgent", Qt::CaseInsensitive) == 0) return Health::Urgent;
        if (value.compare("En soin", Qt::CaseInsensitive) == 0) return Health::EnSoin;
        return Health::Sain;
    }
    QString phoneDigits() const {
        QString value = ui->edittelephone->text();
        value.remove(QRegularExpression("[^0-9]"));
        return value.isEmpty() ? QStringLiteral("0") : value;
    }
    bool matchesSpecies(const Animal &a) const { return ui->btntous->isChecked() || (ui->btnchiens->isChecked() && a.espece == "Chien") || (ui->btnchats->isChecked() && a.espece == "Chat"); }
    void refresh() {
        m_animals = loadAnimals(); const QString text = filterText(); QList<Animal> shown; int good = 0, care = 0, urgent = 0;
        for (const Animal &a : m_animals) {
            if (a.sante == Health::Sain) ++good; else if (a.sante == Health::EnSoin) ++care; else ++urgent;
            const bool matches = text.isEmpty() || a.nom.contains(text, Qt::CaseInsensitive) || a.espece.contains(text, Qt::CaseInsensitive) || a.race.contains(text, Qt::CaseInsensitive) || a.proprietaire.contains(text, Qt::CaseInsensitive) || a.puce.contains(text, Qt::CaseInsensitive);
            if (matchesSpecies(a) && matches) shown.append(a);
        }
        std::sort(shown.begin(), shown.end(), [](const Animal &a, const Animal &b) { return a.nom.localeAwareCompare(b.nom) < 0; });
        ui->tableanimaux->setRowCount(0);
        for (const Animal &a : shown) {
            const int row = ui->tableanimaux->rowCount(); ui->tableanimaux->insertRow(row);
            auto *name = new QTableWidgetItem(QStringLiteral("%1 - %2").arg(a.nom, a.espece)); name->setData(Qt::UserRole, a.id);
            ui->tableanimaux->setItem(row, 0, name); ui->tableanimaux->setItem(row, 1, new QTableWidgetItem(ageText(a.age))); ui->tableanimaux->setItem(row, 2, new QTableWidgetItem(a.proprietaire)); ui->tableanimaux->setItem(row, 3, new QTableWidgetItem(a.telephone));
            auto *status = new QTableWidgetItem(healthText(a.sante)); status->setForeground(healthColor(a.sante)); ui->tableanimaux->setItem(row, 4, status);
        }
        const int total = m_animals.size(); ui->barresains->setValue(total ? qRound(100.0 * good / total) : 0); ui->barreensoin->setValue(total ? qRound(100.0 * care / total) : 0); ui->barreurgent->setValue(total ? qRound(100.0 * urgent / total) : 0); ui->lblcompte->setText(QStringLiteral("%1 sur %2 animaux").arg(shown.size()).arg(total)); updateActions();
    }
    Animal animalById(int id) const { for (const Animal &a : m_animals) if (a.id == id) return a; return {}; }
    int selectedId() const { const int row = ui->tableanimaux->currentRow(); return row >= 0 && ui->tableanimaux->item(row, 0) ? ui->tableanimaux->item(row, 0)->data(Qt::UserRole).toInt() : 0; }
    void updateActions() { const bool selected = selectedId() != 0; ui->btnmodifier->setEnabled(selected); ui->btnsupprimer->setEnabled(selected); }
    void showList() { ui->pagescentre->setCurrentWidget(ui->pageliste); ui->cadreformulaire->hide(); }
    void showForm() { clearForm(); m_editId = 0; ui->lbltitreformulaire->setText("Nouvel animal"); ui->pagescentre->setCurrentWidget(ui->pageliste); ui->cadreformulaire->show(); ui->editnom->setFocus(); }
    void clearForm() { ui->editnom->clear(); ui->editrace->clear(); ui->editpuce->clear(); ui->editproprietaire->clear(); ui->edittelephone->clear(); ui->spinage->setValue(0); ui->comboespece->setCurrentIndex(0); ui->combovaccinal->setCurrentIndex(0); ui->combosante->setCurrentIndex(0); ui->lblerreur->clear(); }
    void saveAnimal() {
        if (ui->editnom->text().trimmed().isEmpty() || ui->editproprietaire->text().trimmed().isEmpty()) { ui->lblerreur->setText("Le nom et le proprietaire sont obligatoires."); return; }
        QSqlQuery query;
        if (m_editId) query.prepare("UPDATE animaux SET nom=?, race=?, date_naissance=ADD_MONTHS(TRUNC(SYSDATE), -12 * ?), etat_sante=?, nom_proprietaire=?, telephone=TO_NUMBER(?), espece=?, puce=?, vaccinal=? WHERE id_animal=?");
        else query.prepare("INSERT INTO animaux (id_animal, nom, race, sexe, date_naissance, allergies, etat_sante, nom_proprietaire, telephone, email, adresse, espece, puce, vaccinal) SELECT NVL(MAX(id_animal), 0) + 1, ?, ?, 'Non renseigne', ADD_MONTHS(TRUNC(SYSDATE), -12 * ?), 'Aucune', ?, ?, TO_NUMBER(?), 'inconnu@pawche.local', 'Non renseignee', ?, ?, ? FROM animaux");
        query.addBindValue(ui->editnom->text().trimmed()); query.addBindValue(ui->editrace->text().trimmed()); query.addBindValue(ui->spinage->value()); query.addBindValue(healthText(static_cast<Health>(ui->combosante->currentIndex()))); query.addBindValue(ui->editproprietaire->text().trimmed()); query.addBindValue(phoneDigits()); query.addBindValue(ui->comboespece->currentText()); query.addBindValue(ui->editpuce->text().trimmed()); query.addBindValue(ui->combovaccinal->currentText());
        if (m_editId) query.addBindValue(m_editId);
        if (!query.exec()) { ui->lblerreur->setText("Erreur base de donnees : " + query.lastError().text()); return; }
        clearForm(); showList(); refresh();
    }
    void editSelected() {
        const Animal a = animalById(selectedId()); if (!a.id) return; m_editId = a.id; ui->lbltitreformulaire->setText("Modifier l'animal");
        ui->editnom->setText(a.nom); ui->comboespece->setCurrentText(a.espece); ui->editrace->setText(a.race); ui->spinage->setValue(a.age); ui->editpuce->setText(a.puce); ui->combovaccinal->setCurrentText(a.vaccinal); ui->editproprietaire->setText(a.proprietaire); ui->edittelephone->setText(a.telephone); ui->combosante->setCurrentIndex(static_cast<int>(a.sante)); ui->pagescentre->setCurrentWidget(ui->pageliste); ui->cadreformulaire->show(); ui->editnom->setFocus();
    }
    void deleteSelected() {
        const int id = selectedId(); if (!id || QMessageBox::question(this, "Supprimer l'animal", "Supprimer cet animal ?") != QMessageBox::Yes) return;
        QSqlQuery query; query.prepare("DELETE FROM animaux WHERE id_animal=?"); query.addBindValue(id);
        if (!query.exec()) { QMessageBox::warning(this, "Base de donnees", query.lastError().text()); return; }
        refresh();
    }
    Ui::MainWindow *ui; QList<Animal> m_animals; int m_editId = 0; QString m_databaseError;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    if (app.arguments().contains("--test-connection")) {
        QTextStream output(stdout);
        if (Connection::instance().open()) { output << "Oracle connection succeeded\n"; return 0; }
        output << "Oracle connection failed: " << Connection::instance().lastError() << '\n';
        return 1;
    }
    if (!Connection::instance().open()) { QMessageBox::critical(nullptr, "Base de donnees", "Connexion Oracle impossible.\n" + Connection::instance().lastError()); return 1; }
    MainWindow window; window.show();
    QMessageBox::information(&window, "Base de donnees", "Connexion Oracle reussie.");
    return app.exec();
}
