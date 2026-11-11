#ifndef PETCARECENTER_H
#define PETCARECENTER_H

#include <QMainWindow>
#include <QList>
#include "employe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Petcarecenter; } // Le namespace correspond au nom de la classe
QT_END_NAMESPACE

class QLabel;

class Petcarecenter : public QMainWindow
{
    Q_OBJECT

public:
    Petcarecenter(QWidget *parent = nullptr);
    ~Petcarecenter();

private slots:
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnVider_clicked();
    void on_btnTrierPrix_clicked();
    void on_btnTrierDate_clicked();
    void on_btnExportPdf_clicked();
    void on_inputSearch_textChanged(const QString &text);
    void on_comboFilterType_currentTextChanged(const QString &text);
    void on_tableCommandes_cellClicked(int row, int column);

private:
    Ui::Petcarecenter *ui; // Modifié ici
    QList<Employe> m_employes;
    QLabel *m_domainStatsLabel;
    bool m_sortAscNom;
    bool m_sortAscPoste;

    void refreshTable();
    void updateStatistics();
    void clearForm();
    QList<Employe> currentFilteredList() const;
    int employeIndex(const QString &id) const;
    Employe employeFromForm() const;
    bool formIsValid();
    void loadEmployes();
};

#endif // PETCARECENTER_H