#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QSettings>

#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Awel ma t7el l'interface: Cacher les champs, labels et boutons de saisie
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);

    ui->lineEdit_id->setVisible(false);
    ui->lineEdit_date->setVisible(false);
    ui->lineEdit_montant->setVisible(false);
    ui->lineEdit_type->setVisible(false);
    ui->lineEdit_qte->setVisible(false);
    ui->lineEdit_etat->setVisible(false);

    ui->btn_modifier->setVisible(false);
    ui->btn_enregistrer->setVisible(false);
    ui->btn_vider->setVisible(false);

    // 2. Configuration du tableau (Interdire la modif directe, selection par ligne)
    ui->tableWidget_commandes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_commandes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_commandes->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget_commandes->setColumnCount(6);
    QStringList labels;
    labels << "ID" << "Date" << "Montant" << "Type" << "Quantité" << "Etat";
    ui->tableWidget_commandes->setHorizontalHeaderLabels(labels);

    // 3. Charger les données enregistrées
    chargerCommandes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- AFFICHER LE FORMULAIRE DE SAISIE / AJOUTER UNE LIGNE ---
// --- AJOUTER UNE NOUVELLE COMMANDE ---
void MainWindow::on_btn_ajouter_clicked()
{
    // 1. Ken el champs mch m7ellin (ou t7eb tansa7hom), n7ellouhom
    if (!ui->lineEdit_id->isVisible()) {
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);

        ui->lineEdit_id->setVisible(true);
        ui->lineEdit_date->setVisible(true);
        ui->lineEdit_montant->setVisible(true);
        ui->lineEdit_type->setVisible(true);
        ui->lineEdit_qte->setVisible(true);
        ui->lineEdit_etat->setVisible(true);

        ui->btn_modifier->setVisible(true);
        ui->btn_enregistrer->setVisible(true);
        ui->btn_vider->setVisible(true);

        // Nfarghou el champs bch tktob fihom mel jdid
        ui->lineEdit_id->clear();
        ui->lineEdit_date->clear();
        ui->lineEdit_montant->clear();
        ui->lineEdit_type->clear();
        ui->lineEdit_qte->clear();
        ui->lineEdit_etat->clear();
        ui->tableWidget_commandes->clearSelection();
        return;
    }

    // 2. 3and el 3abed ki y3awd yenzel 3al Ajouter ba ما ykteb el data:
    QString id = ui->lineEdit_id->text().trimmed();
    QString date = ui->lineEdit_date->text().trimmed();
    QString montant = ui->lineEdit_montant->text().trimmed();
    QString type = ui->lineEdit_type->text().trimmed();
    QString qte = ui->lineEdit_qte->text().trimmed();
    QString etat = ui->lineEdit_etat->text().trimmed();

    if (id.isEmpty() || montant.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Remplis au moins l'ID et le Montant !");
        return;
    }

    // Nansiw ay selection 9dima bch ma nmodifiw 7atta chay bel ghalat
    ui->tableWidget_commandes->clearSelection();

    // DIMA NZIDOU LIGNE JDIDA FEL A5IR (Jamais modification houni)
    int row = ui->tableWidget_commandes->rowCount();
    ui->tableWidget_commandes->insertRow(row);

    ui->tableWidget_commandes->setItem(row, 0, new QTableWidgetItem(id));
    ui->tableWidget_commandes->setItem(row, 1, new QTableWidgetItem(date));
    ui->tableWidget_commandes->setItem(row, 2, new QTableWidgetItem(montant));
    ui->tableWidget_commandes->setItem(row, 3, new QTableWidgetItem(type));
    ui->tableWidget_commandes->setItem(row, 4, new QTableWidgetItem(qte));
    ui->tableWidget_commandes->setItem(row, 5, new QTableWidgetItem(etat));

    // Nfarghou el champs w nupdatew el stats
    ui->lineEdit_id->clear();
    ui->lineEdit_date->clear();
    ui->lineEdit_montant->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_qte->clear();
    ui->lineEdit_etat->clear();

    afficherStatistiques();

    QMessageBox::information(this, "Succès", "Nouvelle commande ajoutée au tableau ! N'oublie pas de cliquer sur Enregistrer.");
}

// --- MODIFIER LA LIGNE SÉLECTIONNÉE ---
void MainWindow::on_btn_modifier_clicked()
{
    int row = ui->tableWidget_commandes->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Attention", "Sélectionne d'abord une ligne dans le tableau à modifier !");
        return;
    }

    ui->tableWidget_commandes->setItem(row, 0, new QTableWidgetItem(ui->lineEdit_id->text()));
    ui->tableWidget_commandes->setItem(row, 1, new QTableWidgetItem(ui->lineEdit_date->text()));
    ui->tableWidget_commandes->setItem(row, 2, new QTableWidgetItem(ui->lineEdit_montant->text()));
    ui->tableWidget_commandes->setItem(row, 3, new QTableWidgetItem(ui->lineEdit_type->text()));
    ui->tableWidget_commandes->setItem(row, 4, new QTableWidgetItem(ui->lineEdit_qte->text()));
    ui->tableWidget_commandes->setItem(row, 5, new QTableWidgetItem(ui->lineEdit_etat->text()));

    // Mettre à jour les statistiques après la modification
    afficherStatistiques();

    QMessageBox::information(this, "Modification", "Ligne modifiée ! N'oublie pas de cliquer sur Enregistrer.");
}

// --- VIDER LES CHAMPS ---
// --- VIDER LES CHAMPS SEULEMENT (SANS TOUCHER AU TABLEAU NI EFFACER DE LIGNES) ---
// --- VIDER / SUPPRIMER LA LIGNE SÉLECTIONNÉE DU TABLEAU ---
void MainWindow::on_btn_vider_clicked()
{
    int row = ui->tableWidget_commandes->currentRow();

    // Ken fama ligne mselectiha, nfas5ouha mel tableau
    if (row >= 0) {
        ui->tableWidget_commandes->removeRow(row);

        // Nsauvegardiw el changement jdid fel QSettings
        sauvegarderCommandes();

        // Mettre à jour les statistiques
        afficherStatistiques();
    }

    // Vider zeda el champs de saisie
    ui->lineEdit_id->clear();
    ui->lineEdit_date->clear();
    ui->lineEdit_montant->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_qte->clear();
    ui->lineEdit_etat->clear();

    ui->tableWidget_commandes->clearSelection();
}

// --- ENREGISTRER (SAUVEGARDE GLOBALE + GESTION SUPPRESSION) ---
// --- ENREGISTRER (SAUVEGARDE GLOBALE DU TABLEAU) ---
// --- ENREGISTRER (AJOUT OU MISE À JOUR SÛRE) ---
void MainWindow::on_btn_enregistrer_clicked()
{
    // Sauvegarder tout le contenu actuel du tableau dans QSettings (persistance)
    sauvegarderCommandes();

    // Mettre à jour les statistiques pour être synchro
    afficherStatistiques();

    QMessageBox::information(this, "Enregistrement", "Toutes les modifications ont été enregistrées avec succès !");
}
void MainWindow::sauvegarderCommandes()
{
    QSettings settings("PawcheOrg", "GestionCommandes");
    settings.remove("commandesList");

    int rowCount = ui->tableWidget_commandes->rowCount();
    settings.beginWriteArray("commandesList");

    for (int i = 0; i < rowCount; ++i) {
        settings.setArrayIndex(i);
        settings.setValue("id", ui->tableWidget_commandes->item(i, 0) ? ui->tableWidget_commandes->item(i, 0)->text() : "");
        settings.setValue("date", ui->tableWidget_commandes->item(i, 1) ? ui->tableWidget_commandes->item(i, 1)->text() : "");
        settings.setValue("montant", ui->tableWidget_commandes->item(i, 2) ? ui->tableWidget_commandes->item(i, 2)->text() : "");
        settings.setValue("type", ui->tableWidget_commandes->item(i, 3) ? ui->tableWidget_commandes->item(i, 3)->text() : "");
        settings.setValue("qte", ui->tableWidget_commandes->item(i, 4) ? ui->tableWidget_commandes->item(i, 4)->text() : "");
        settings.setValue("etat", ui->tableWidget_commandes->item(i, 5) ? ui->tableWidget_commandes->item(i, 5)->text() : "");
    }
    settings.endArray();
}

void MainWindow::chargerCommandes()
{
    QSettings settings("PawcheOrg", "GestionCommandes");
    int size = settings.beginReadArray("commandesList");

    if (size > 0) {
        ui->tableWidget_commandes->setRowCount(size);
        for (int i = 0; i < size; ++i) {
            settings.setArrayIndex(i);
            ui->tableWidget_commandes->setItem(i, 0, new QTableWidgetItem(settings.value("id").toString()));
            ui->tableWidget_commandes->setItem(i, 1, new QTableWidgetItem(settings.value("date").toString()));
            ui->tableWidget_commandes->setItem(i, 2, new QTableWidgetItem(settings.value("montant").toString()));
            ui->tableWidget_commandes->setItem(i, 3, new QTableWidgetItem(settings.value("type").toString()));
            ui->tableWidget_commandes->setItem(i, 4, new QTableWidgetItem(settings.value("qte").toString()));
            ui->tableWidget_commandes->setItem(i, 5, new QTableWidgetItem(settings.value("etat").toString()));
        }
    } else {
        ui->tableWidget_commandes->setRowCount(4);

        ui->tableWidget_commandes->setItem(0, 0, new QTableWidgetItem("CMD001"));
        ui->tableWidget_commandes->setItem(0, 1, new QTableWidgetItem("1/10/2026"));
        ui->tableWidget_commandes->setItem(0, 2, new QTableWidgetItem("300 DT"));
        ui->tableWidget_commandes->setItem(0, 3, new QTableWidgetItem("Alimentation"));
        ui->tableWidget_commandes->setItem(0, 4, new QTableWidgetItem("2"));
        ui->tableWidget_commandes->setItem(0, 5, new QTableWidgetItem("Livrée"));

        ui->tableWidget_commandes->setItem(1, 0, new QTableWidgetItem("CMD002"));
        ui->tableWidget_commandes->setItem(1, 1, new QTableWidgetItem("25/5/2026"));
        ui->tableWidget_commandes->setItem(1, 2, new QTableWidgetItem("200 DT"));
        ui->tableWidget_commandes->setItem(1, 3, new QTableWidgetItem("Accessoires"));
        ui->tableWidget_commandes->setItem(1, 4, new QTableWidgetItem("1"));
        ui->tableWidget_commandes->setItem(1, 5, new QTableWidgetItem("Livrées"));

        ui->tableWidget_commandes->setItem(2, 0, new QTableWidgetItem("CMD003"));
        ui->tableWidget_commandes->setItem(2, 1, new QTableWidgetItem("30/6/2026"));
        ui->tableWidget_commandes->setItem(2, 2, new QTableWidgetItem("450 DT"));
        ui->tableWidget_commandes->setItem(2, 3, new QTableWidgetItem("Soins"));
        ui->tableWidget_commandes->setItem(2, 4, new QTableWidgetItem("3"));
        ui->tableWidget_commandes->setItem(2, 5, new QTableWidgetItem("Validées"));

        ui->tableWidget_commandes->setItem(3, 0, new QTableWidgetItem("CMD004"));
        ui->tableWidget_commandes->setItem(3, 1, new QTableWidgetItem("30/9/2026"));
        ui->tableWidget_commandes->setItem(3, 2, new QTableWidgetItem("400 DT"));
        ui->tableWidget_commandes->setItem(3, 3, new QTableWidgetItem("Jouets"));
        ui->tableWidget_commandes->setItem(3, 4, new QTableWidgetItem("1"));
        ui->tableWidget_commandes->setItem(3, 5, new QTableWidgetItem("En attente"));
    }
    settings.endArray();

    // Calculer les statistiques dès le chargement
    afficherStatistiques();
}

// --- GESTION DES STATISTIQUES SELON L'ÉTAT (FRAME 9, 10, 11) ---
void MainWindow::afficherStatistiques()
{
    int countLivrees = 0;
    int countValidees = 0;
    int countEnAttente = 0;
    int totalVisible = 0;

    for (int i = 0; i < ui->tableWidget_commandes->rowCount(); ++i) {
        if (ui->tableWidget_commandes->isRowHidden(i)) continue;

        totalVisible++;
        QTableWidgetItem *item = ui->tableWidget_commandes->item(i, 5); // Colonne État
        if (item) {
            QString etat = item->text().trimmed().toLower();

            if (etat.contains("livr")) {
                countLivrees++;
            }
            else if (etat.contains("valid")) {
                countValidees++;
            }
            else if (etat.contains("attente")) {
                countEnAttente++;
            }
        }
    }

    // Calcul des pourcentages réels
    double pLivrees = 0.0;
    double pValidees = 0.0;
    double pEnAttente = 0.0;

    if (totalVisible > 0) {
        pLivrees = (double)countLivrees * 100.0 / totalVisible;
        pValidees = (double)countValidees * 100.0 / totalVisible;
        pEnAttente = (double)countEnAttente * 100.0 / totalVisible;
    }

    // Affichage des pourcentages dans les Labels
    ui->label_pct_livrees->setText(QString::number(pLivrees, 'f', 0) + "%");
    ui->label_pct_validees->setText(QString::number(pValidees, 'f', 0) + "%");
    ui->label_pct_attente->setText(QString::number(pEnAttente, 'f', 0) + "%");

    // Hauteur maximale du rectangle (par exemple 90 pixels pour laisser de la place au texte au-dessus)
    int maxHeight = 90;

    // Le calcul de la hauteur est maintenant basé DIRECTEMENT sur le pourcentage !
    int hLivrees   = (pLivrees * maxHeight) / 100.0;
    int hValidees  = (pValidees * maxHeight) / 100.0;
    int hEnAttente = (pEnAttente * maxHeight) / 100.0;

    // Minimum pour voir la barre si le count > 0
    if (countLivrees > 0 && hLivrees < 8)        hLivrees = 8;
    if (countValidees > 0 && hValidees < 8)     hValidees = 8;
    if (countEnAttente > 0 && hEnAttente < 8)   hEnAttente = 8;

    // Ligne de base
    // Ligne de base alignée directement sur le trait horizontal (frame_7)
    int baselineY = ui->frame_7->y() + 4.5;
    // Positionnement des barres
    ui->frame_9->setGeometry(ui->frame_9->x(), baselineY - hLivrees, ui->frame_9->width(), hLivrees);
    ui->frame_10->setGeometry(ui->frame_10->x(), baselineY - hEnAttente, ui->frame_10->width(), hEnAttente);
    ui->frame_11->setGeometry(ui->frame_11->x(), baselineY - hValidees, ui->frame_11->width(), hValidees);

    // Positionnement des labels des pourcentages au-dessus des barres avec un espacement sécurisé
    ui->label_pct_livrees->move(ui->frame_9->x(), (baselineY - hLivrees) - 28);
    ui->label_pct_validees->move(ui->frame_11->x(), (baselineY - hValidees) - 28);
    ui->label_pct_attente->move(ui->frame_10->x(), (baselineY - hEnAttente) - 28);
}
// --- RECHERCHE ---
void MainWindow::on_lineEdit_recherche_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget_commandes->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->tableWidget_commandes->columnCount(); ++j) {
            QTableWidgetItem *item = ui->tableWidget_commandes->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_commandes->setRowHidden(i, !match);
    }
    // Mettre à jour les stats selon les éléments affichés après recherche
    afficherStatistiques();
}

// --- TRI ---
void MainWindow::on_comboBox_tri_currentIndexChanged(int index)
{
    if (index == 1) {
        ui->tableWidget_commandes->sortItems(2, Qt::AscendingOrder);
    } else if (index == 2) {
        ui->tableWidget_commandes->sortItems(1, Qt::AscendingOrder);
    }
}

// --- EXPORT PDF ---
// --- EXPORT PDF VRAI ---
void MainWindow::on_btn_exporter_pdf_clicked()
{
    // 1. Demander à l'utilisateur où enregistrer le fichier PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "commandes.pdf", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty())
        return;

    // 2. Construire le contenu HTML du document PDF
    QString html = "<h2 style='text-align: center; color: #333;'>Liste des Commandes</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='5' style='width: 100%; border-collapse: collapse; text-align: center;'>";
    html += "<tr style='background-color: #f2f2f2;'>";
    html += "<th>ID</th><th>Date</th><th>Montant</th><th>Type</th><th>Quantité</th><th>État</th>";
    html += "</tr>";

    // 3. Remplir le tableau HTML avec les données du tableWidget
    for (int i = 0; i < ui->tableWidget_commandes->rowCount(); ++i) {
        if (ui->tableWidget_commandes->isRowHidden(i)) continue; // Ignorer les lignes cachées (par la recherche)

        html += "<tr>";
        for (int j = 0; j < ui->tableWidget_commandes->columnCount(); ++j) {
            QTableWidgetItem *item = ui->tableWidget_commandes->item(i, j);
            QString text = item ? item->text() : "";
            html += "<td>" + text + "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    // 4. Générer le fichier PDF réel
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QTextDocument document;
    document.setHtml(html);
    document.print(&pdfWriter);

    QMessageBox::information(this, "Succès", "Le fichier PDF a été exporté avec succès !");
}
// --- CLIC SUR LE TABLEAU (Remplit les LineEdits pour modification, SANS ajouter de ligne) ---
void MainWindow::on_tableWidget_commandes_itemClicked(QTableWidgetItem *item)
{
    // Afficher les champs si ce n'est pas déjà fait
    if (!ui->lineEdit_id->isVisible()) {
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);

        ui->lineEdit_id->setVisible(true);
        ui->lineEdit_date->setVisible(true);
        ui->lineEdit_montant->setVisible(true);
        ui->lineEdit_type->setVisible(true);
        ui->lineEdit_qte->setVisible(true);
        ui->lineEdit_etat->setVisible(true);

        ui->btn_modifier->setVisible(true);
        ui->btn_enregistrer->setVisible(true);
        ui->btn_vider->setVisible(true);
    }

    int row = item->row();
    if(ui->tableWidget_commandes->item(row, 0)) ui->lineEdit_id->setText(ui->tableWidget_commandes->item(row, 0)->text());
    if(ui->tableWidget_commandes->item(row, 1)) ui->lineEdit_date->setText(ui->tableWidget_commandes->item(row, 1)->text());
    if(ui->tableWidget_commandes->item(row, 2)) ui->lineEdit_montant->setText(ui->tableWidget_commandes->item(row, 2)->text());
    if(ui->tableWidget_commandes->item(row, 3)) ui->lineEdit_type->setText(ui->tableWidget_commandes->item(row, 3)->text());
    if(ui->tableWidget_commandes->item(row, 4)) ui->lineEdit_qte->setText(ui->tableWidget_commandes->item(row, 4)->text());
    if(ui->tableWidget_commandes->item(row, 5)) ui->lineEdit_etat->setText(ui->tableWidget_commandes->item(row, 5)->text());
}