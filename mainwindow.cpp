#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDateTime>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_sortAscPrix(true),
      m_sortAscDate(true)
{
    ui->setupUi(this);

    // Initial setup
    ui->dateLivraison->setDate(QDate::currentDate());

    // Configure table headers and appearance
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui->tableCommandes->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);

    // Load initial realistic sample data
    loadSampleData();
    refreshTable(m_commandes);
    updateStatistics();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSampleData()
{
    m_commandes.append(Commande("CMD-2026-01", QDate(2026, 10, 5),  750.500, "Alimentation", 40, "Livrée"));
    m_commandes.append(Commande("CMD-2026-02", QDate(2026, 10, 8),  420.000, "Soin & Santé", 15, "En attente"));
    m_commandes.append(Commande("CMD-2026-03", QDate(2026, 10, 10), 185.300, "Accessoire",   25, "Confirmée"));
    m_commandes.append(Commande("CMD-2026-04", QDate(2026, 10, 12), 920.750, "Alimentation", 50, "En cours"));
    m_commandes.append(Commande("CMD-2026-05", QDate(2026, 10, 15), 310.000, "Hygiène",      30, "En attente"));
    m_commandes.append(Commande("CMD-2026-06", QDate(2026, 10, 18), 1250.000,"Équipement",    5, "Confirmée"));
    m_commandes.append(Commande("CMD-2026-07", QDate(2026, 10, 20), 140.000, "Soin & Santé", 10, "En attente"));
}

void MainWindow::refreshTable(const QList<Commande> &list)
{
    ui->tableCommandes->setRowCount(0);

    for (int i = 0; i < list.size(); ++i) {
        const Commande &cmd = list.at(i);
        ui->tableCommandes->insertRow(i);

        // ID Commande
        QTableWidgetItem *itemId = new QTableWidgetItem(cmd.id());
        itemId->setTextAlignment(Qt::AlignCenter);

        // Date livraison
        QTableWidgetItem *itemDate = new QTableWidgetItem(cmd.dateLivraison().toString("dd/MM/yyyy"));
        itemDate->setTextAlignment(Qt::AlignCenter);

        // Montant
        QTableWidgetItem *itemMontant = new QTableWidgetItem(QString::number(cmd.montant(), 'f', 3) + " DT");
        itemMontant->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemMontant->setFont(QFont("Segoe UI", 10, QFont::Bold));

        // Type produit
        QTableWidgetItem *itemType = new QTableWidgetItem(cmd.typeProduit());
        itemType->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        // Quantité
        QTableWidgetItem *itemQte = new QTableWidgetItem(QString::number(cmd.quantite()));
        itemQte->setTextAlignment(Qt::AlignCenter);

        // État with pastel badges
        QTableWidgetItem *itemEtat = new QTableWidgetItem(cmd.etat());
        itemEtat->setTextAlignment(Qt::AlignCenter);

        if (cmd.etat() == "Livrée") {
            itemEtat->setForeground(QColor("#2E7D32"));
            itemEtat->setBackground(QColor("#E8F5E9"));
        } else if (cmd.etat() == "En attente") {
            itemEtat->setForeground(QColor("#C62828"));
            itemEtat->setBackground(QColor("#FFEBEE"));
        } else if (cmd.etat() == "Confirmée") {
            itemEtat->setForeground(QColor("#1565C0"));
            itemEtat->setBackground(QColor("#E3F2FD"));
        } else if (cmd.etat() == "En cours") {
            itemEtat->setForeground(QColor("#E65100"));
            itemEtat->setBackground(QColor("#FFF3E0"));
        } else {
            itemEtat->setForeground(QColor("#616161"));
            itemEtat->setBackground(QColor("#EEEEEE"));
        }

        ui->tableCommandes->setItem(i, 0, itemId);
        ui->tableCommandes->setItem(i, 1, itemDate);
        ui->tableCommandes->setItem(i, 2, itemMontant);
        ui->tableCommandes->setItem(i, 3, itemType);
        ui->tableCommandes->setItem(i, 4, itemQte);
        ui->tableCommandes->setItem(i, 5, itemEtat);
    }
}

void MainWindow::updateStatistics()
{
    QMap<QString, int> statusCount;
    statusCount["En attente"] = 0;
    statusCount["Confirmée"]  = 0;
    statusCount["En cours"]   = 0;
    statusCount["Livrée"]     = 0;
    statusCount["Annulée"]    = 0;

    double totalMontant = 0.0;
    int enAttente = 0;

    for (const Commande &cmd : m_commandes) {
        statusCount[cmd.etat()] = statusCount.value(cmd.etat(), 0) + 1;
        totalMontant += cmd.montant();
        if (cmd.etat() == "En attente") {
            enAttente++;
        }
    }

    // Update curve widget
    ui->widgetCurve->updateData(statusCount);

    // Update alert card
    ui->lblAlertBadge->setText(QString::number(enAttente));
    ui->lblAlertDesc->setText(QString("%1 en attente sur %2 total").arg(enAttente).arg(m_commandes.size()));
    ui->lblTotalMontant->setText(QString("Total: %1 DT").arg(QString::number(totalMontant, 'f', 3)));
}

void MainWindow::clearForm()
{
    ui->txtId->clear();
    ui->dateLivraison->setDate(QDate::currentDate());
    ui->spinMontant->setValue(0.0);
    ui->comboType->setCurrentIndex(0);
    ui->spinQuantite->setValue(1);
    ui->comboEtat->setCurrentIndex(0);
    ui->txtId->setEnabled(true);
}

QList<Commande> MainWindow::currentFilteredList() const
{
    QString query = ui->inputSearch->text().trimmed().toLower();
    QString filterType = ui->comboFilterType->currentText();

    QList<Commande> filtered;
    for (const Commande &cmd : m_commandes) {
        bool matchesType = (filterType == "Tous les types") || 
                           (cmd.typeProduit().compare(filterType, Qt::CaseInsensitive) == 0);
        
        bool matchesQuery = query.isEmpty() ||
                            cmd.typeProduit().toLower().contains(query) ||
                            cmd.id().toLower().contains(query) ||
                            cmd.etat().toLower().contains(query);

        if (matchesType && matchesQuery) {
            filtered.append(cmd);
        }
    }
    return filtered;
}

void MainWindow::on_btnAjouter_clicked()
{
    QString id = ui->txtId->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Champs requis", "Veuillez saisir un identifiant de commande.");
        ui->txtId->setFocus();
        return;
    }

    // Check duplicate ID
    for (const Commande &cmd : m_commandes) {
        if (cmd.id().compare(id, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, "Doublon", "Une commande avec cet identifiant existe déjà !");
            return;
        }
    }

    double montant = ui->spinMontant->value();
    if (montant <= 0.0) {
        QMessageBox::warning(this, "Montant invalide", "Le montant doit être supérieur à 0.");
        return;
    }

    Commande newCmd(id,
                    ui->dateLivraison->date(),
                    montant,
                    ui->comboType->currentText(),
                    ui->spinQuantite->value(),
                    ui->comboEtat->currentText());

    m_commandes.append(newCmd);
    refreshTable(currentFilteredList());
    updateStatistics();
    clearForm();

    QMessageBox::information(this, "Succès", "La commande a été ajoutée avec succès !");
}

void MainWindow::on_btnModifier_clicked()
{
    int currentRow = ui->tableCommandes->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une commande dans le tableau pour la modifier.");
        return;
    }

    QString id = ui->tableCommandes->item(currentRow, 0)->text();
    int targetIndex = -1;
    for (int i = 0; i < m_commandes.size(); ++i) {
        if (m_commandes[i].id() == id) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex >= 0) {
        m_commandes[targetIndex].setDateLivraison(ui->dateLivraison->date());
        m_commandes[targetIndex].setMontant(ui->spinMontant->value());
        m_commandes[targetIndex].setTypeProduit(ui->comboType->currentText());
        m_commandes[targetIndex].setQuantite(ui->spinQuantite->value());
        m_commandes[targetIndex].setEtat(ui->comboEtat->currentText());

        refreshTable(currentFilteredList());
        updateStatistics();
        clearForm();

        QMessageBox::information(this, "Succès", "La commande a été modifiée avec succès !");
    }
}

void MainWindow::on_btnSupprimer_clicked()
{
    int currentRow = ui->tableCommandes->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner une commande à supprimer.");
        return;
    }

    QString id = ui->tableCommandes->item(currentRow, 0)->text();

    auto reply = QMessageBox::question(this, "Confirmation",
                                       QString("Êtes-vous sûr de vouloir supprimer la commande '%1' ?").arg(id),
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        for (int i = 0; i < m_commandes.size(); ++i) {
            if (m_commandes[i].id() == id) {
                m_commandes.removeAt(i);
                break;
            }
        }
        refreshTable(currentFilteredList());
        updateStatistics();
        clearForm();
        QMessageBox::information(this, "Supprimé", "La commande a été supprimée.");
    }
}

void MainWindow::on_btnVider_clicked()
{
    clearForm();
}

void MainWindow::on_tableCommandes_cellClicked(int row, int /*column*/)
{
    if (row < 0) return;

    QString id = ui->tableCommandes->item(row, 0)->text();
    for (const Commande &cmd : m_commandes) {
        if (cmd.id() == id) {
            ui->txtId->setText(cmd.id());
            ui->txtId->setEnabled(false); // ID should not be changed on edit
            ui->dateLivraison->setDate(cmd.dateLivraison());
            ui->spinMontant->setValue(cmd.montant());
            ui->comboType->setCurrentText(cmd.typeProduit());
            ui->spinQuantite->setValue(cmd.quantite());
            ui->comboEtat->setCurrentText(cmd.etat());
            break;
        }
    }
}

void MainWindow::on_btnTrierPrix_clicked()
{
    std::sort(m_commandes.begin(), m_commandes.end(), [this](const Commande &a, const Commande &b) {
        return m_sortAscPrix ? (a.montant() < b.montant()) : (a.montant() > b.montant());
    });

    m_sortAscPrix = !m_sortAscPrix;
    ui->btnTrierPrix->setText(m_sortAscPrix ? "↕ Trier par prix (Croissant)" : "↕ Trier par prix (Décroissant)");
    refreshTable(currentFilteredList());
}

void MainWindow::on_btnTrierDate_clicked()
{
    std::sort(m_commandes.begin(), m_commandes.end(), [this](const Commande &a, const Commande &b) {
        return m_sortAscDate ? (a.dateLivraison() < b.dateLivraison()) : (a.dateLivraison() > b.dateLivraison());
    });

    m_sortAscDate = !m_sortAscDate;
    ui->btnTrierDate->setText(m_sortAscDate ? "📅 Trier par date (Plus ancienne)" : "📅 Trier par date (Plus récente)");
    refreshTable(currentFilteredList());
}

void MainWindow::on_inputSearch_textChanged(const QString &)
{
    refreshTable(currentFilteredList());
}

void MainWindow::on_comboFilterType_currentTextChanged(const QString &)
{
    refreshTable(currentFilteredList());
}

void MainWindow::on_btnExportPdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter les commandes en PDF",
                                                    "Commandes_Fournisseurs.pdf",
                                                    "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty()) return;

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    QList<Commande> listToExport = currentFilteredList();
    double total = 0.0;
    for (const Commande &c : listToExport) {
        total += c.montant();
    }

    QString html;
    html += "<!DOCTYPE html><html><head><style>";
    html += "body { font-family: 'Segoe UI', Arial, sans-serif; color: #3D2619; margin: 30px; }";
    html += "h1 { color: #5C3826; text-align: center; margin-bottom: 4px; font-size: 24px; }";
    html += "h3 { color: #8C7A70; text-align: center; margin-top: 0px; font-weight: normal; font-size: 13px; }";
    html += ".header-table { width: 100%; border: none; margin-bottom: 25px; }";
    html += "table.data-table { width: 100%; border-collapse: collapse; margin-top: 15px; }";
    html += "table.data-table th { background-color: #5C3826; color: #ffffff; padding: 10px 8px; border: 1px solid #5C3826; font-size: 11px; }";
    html += "table.data-table td { padding: 9px 8px; border: 1px solid #EFE6DF; font-size: 11px; text-align: center; }";
    html += "table.data-table tr:nth-child(even) { background-color: #FAF5F0; }";
    html += ".total-box { margin-top: 25px; padding: 14px; background-color: #F8EEE6; border-left: 5px solid #5C3826; font-weight: bold; font-size: 13px; }";
    html += ".footer { margin-top: 40px; text-align: center; font-size: 10px; color: #A68F81; }";
    html += "</style></head><body>";

    html += "<h1>🐾 Pawché - Smart Pet Center</h1>";
    html += "<h3>Rapport de Gestion des Commandes Fournisseurs</h3>";

    html += "<table class='header-table'>";
    html += "<tr>";
    html += "<td><strong>Date d'exportation :</strong> " + QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm") + "</td>";
    html += "<td align='right'><strong>Nombre de commandes :</strong> " + QString::number(listToExport.size()) + "</td>";
    html += "</tr></table>";

    html += "<table class='data-table'>";
    html += "<thead><tr>";
    html += "<th>ID Commande</th>";
    html += "<th>Date livraison</th>";
    html += "<th>Type produit</th>";
    html += "<th>Quantité</th>";
    html += "<th>Montant (DT)</th>";
    html += "<th>État</th>";
    html += "</tr></thead><tbody>";

    for (const Commande &cmd : listToExport) {
        html += "<tr>";
        html += "<td><strong>" + cmd.id() + "</strong></td>";
        html += "<td>" + cmd.dateLivraison().toString("dd/MM/yyyy") + "</td>";
        html += "<td align='left'>" + cmd.typeProduit() + "</td>";
        html += "<td>" + QString::number(cmd.quantite()) + "</td>";
        html += "<td align='right'><strong>" + QString::number(cmd.montant(), 'f', 3) + " DT</strong></td>";
        html += "<td>" + cmd.etat() + "</td>";
        html += "</tr>";
    }

    html += "</tbody></table>";

    html += "<div class='total-box'>";
    html += "Montant Total des Commandes : <span style='color: #633927; font-size: 15px;'>" + QString::number(total, 'f', 3) + " DT</span>";
    html += "</div>";

    html += "<div class='footer'>";
    html += "Document officiel généré par l'application Pawché • Tous droits réservés";
    html += "</div>";
    html += "</body></html>";

    QTextDocument doc;
    doc.setHtml(html);

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);
    doc.print(&writer);

    QMessageBox::information(this, "Exportation réussie",
                             QString("Le fichier PDF a été généré avec succès :\n%1").arg(filePath));
}
