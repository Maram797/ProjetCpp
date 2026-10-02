#include <QApplication>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QTableWidget>
#include <algorithm>

#include "animal.h"
#include "ui_mainwindow.h"

class MainWindow final : public QMainWindow {
public:
    MainWindow() : ui(new Ui::MainWindow) {
        ui->setupUi(this);
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
        seed(); refresh();
    }
    ~MainWindow() override { delete ui; }
private:
    void seed() {
        m_animals = {{1,"Milo","Chien","Golden Retriever",4,"250269699999001","À jour","Mounir","+216 12345678",Health::Sain},
                     {2,"Luna","Chat","Européen",2,"250269699999002","À jour","Sara","+216 98765432",Health::EnSoin},
                     {3,"Rex","Chien","Berger Allemand",7,"250269699999003","En retard","Karim","+216 55512345",Health::Urgent}};
        m_nextId = 4;
    }
    QString filterText() const { return (ui->editrecherche->text() + ' ' + ui->editfiltre->text()).trimmed(); }
    bool matchesSpecies(const Animal &a) const {
        return ui->btntous->isChecked() || (ui->btnchiens->isChecked() && a.espece == "Chien") || (ui->btnchats->isChecked() && a.espece == "Chat");
    }
    void refresh() {
        const QString query = filterText(); QList<Animal> shown; int good = 0, care = 0, urgent = 0;
        for (const Animal &a : m_animals) {
            if (a.sante == Health::Sain) ++good; else if (a.sante == Health::EnSoin) ++care; else ++urgent;
            const bool matchesQuery = query.isEmpty() || a.nom.contains(query, Qt::CaseInsensitive) || a.espece.contains(query, Qt::CaseInsensitive)
                || a.race.contains(query, Qt::CaseInsensitive) || a.proprietaire.contains(query, Qt::CaseInsensitive) || a.puce.contains(query, Qt::CaseInsensitive);
            if (matchesSpecies(a) && matchesQuery) shown.append(a);
        }
        std::sort(shown.begin(), shown.end(), [](const Animal &a, const Animal &b) { return a.nom.localeAwareCompare(b.nom) < 0; });
        ui->tableanimaux->setRowCount(0);
        for (const Animal &a : shown) {
            const int row = ui->tableanimaux->rowCount(); ui->tableanimaux->insertRow(row);
            auto *name = new QTableWidgetItem(QStringLiteral("%1  •  %2").arg(a.nom, a.espece)); name->setData(Qt::UserRole, a.id);
            ui->tableanimaux->setItem(row, 0, name); ui->tableanimaux->setItem(row, 1, new QTableWidgetItem(ageText(a.age)));
            ui->tableanimaux->setItem(row, 2, new QTableWidgetItem(a.proprietaire)); ui->tableanimaux->setItem(row, 3, new QTableWidgetItem(a.telephone));
            auto *status = new QTableWidgetItem(healthText(a.sante)); status->setForeground(healthColor(a.sante)); ui->tableanimaux->setItem(row, 4, status);
        }
        const int total = m_animals.size();
        ui->barresains->setValue(total ? qRound(100.0 * good / total) : 0); ui->barreensoin->setValue(total ? qRound(100.0 * care / total) : 0); ui->barreurgent->setValue(total ? qRound(100.0 * urgent / total) : 0);
        ui->lblsante->setText(total ? QStringLiteral("●  %1% des animaux en bonne santé (%2/%3)").arg(qRound(100.0 * good / total)).arg(good).arg(total) : "●  Aucun animal enregistré");
        ui->lblcompte->setText(QStringLiteral("%1 sur %2 animaux").arg(shown.size()).arg(total)); updateActions();
    }
    Animal *animalById(int id) { for (Animal &a : m_animals) if (a.id == id) return &a; return nullptr; }
    int selectedId() const { const int row = ui->tableanimaux->currentRow(); return row >= 0 && ui->tableanimaux->item(row, 0) ? ui->tableanimaux->item(row, 0)->data(Qt::UserRole).toInt() : 0; }
    void updateActions() { const bool selected = selectedId() != 0; ui->btnmodifier->setEnabled(selected); ui->btnsupprimer->setEnabled(selected); }
    void showList() { ui->pagescentre->setCurrentWidget(ui->pageliste); }
    void showForm() { clearForm(); m_editId = 0; ui->lbltitreformulaire->setText("Nouvel animal"); ui->pagescentre->setCurrentWidget(ui->pageformulaire); ui->editnom->setFocus(); }
    void clearForm() {
        ui->editnom->clear(); ui->editrace->clear(); ui->editpuce->clear(); ui->editproprietaire->clear(); ui->edittelephone->clear(); ui->spinage->setValue(0);
        ui->comboespece->setCurrentIndex(0); ui->combovaccinal->setCurrentIndex(0); ui->combosante->setCurrentIndex(0); ui->lblerreur->clear();
    }
    void saveAnimal() {
        if (ui->editnom->text().trimmed().isEmpty() || ui->editproprietaire->text().trimmed().isEmpty()) { ui->lblerreur->setText("Le nom de l'animal et le propriétaire sont obligatoires."); return; }
        Animal fresh; Animal *a = m_editId ? animalById(m_editId) : nullptr; if (!a) { fresh.id = m_nextId++; a = &fresh; }
        a->nom = ui->editnom->text().trimmed(); a->espece = ui->comboespece->currentText(); a->race = ui->editrace->text().trimmed(); a->age = ui->spinage->value(); a->puce = ui->editpuce->text().trimmed(); a->vaccinal = ui->combovaccinal->currentText(); a->proprietaire = ui->editproprietaire->text().trimmed(); a->telephone = ui->edittelephone->text().trimmed(); a->sante = static_cast<Health>(ui->combosante->currentIndex());
        if (!m_editId) m_animals.append(fresh); clearForm(); showList(); refresh();
    }
    void editSelected() {
        Animal *a = animalById(selectedId()); if (!a) return; m_editId = a->id; ui->lbltitreformulaire->setText("Modifier l'animal");
        ui->editnom->setText(a->nom); ui->comboespece->setCurrentText(a->espece); ui->editrace->setText(a->race); ui->spinage->setValue(a->age); ui->editpuce->setText(a->puce); ui->combovaccinal->setCurrentText(a->vaccinal); ui->editproprietaire->setText(a->proprietaire); ui->edittelephone->setText(a->telephone); ui->combosante->setCurrentIndex(static_cast<int>(a->sante)); ui->pagescentre->setCurrentWidget(ui->pageformulaire);
    }
    void deleteSelected() {
        const int id = selectedId(); if (!id) return; if (QMessageBox::question(this, "Supprimer l'animal", "Supprimer cet animal ?") != QMessageBox::Yes) return;
        for (int i = 0; i < m_animals.size(); ++i) if (m_animals[i].id == id) { m_animals.removeAt(i); break; } refresh();
    }
    Ui::MainWindow *ui; QList<Animal> m_animals; int m_nextId = 1; int m_editId = 0;
};
int main(int argc, char *argv[]) { QApplication app(argc, argv); MainWindow window; window.show(); return app.exec(); }
