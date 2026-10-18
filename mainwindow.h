#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "employe.h" // On inclut la structure séparée

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAjouter_clicked();
    void on_btnModifier_clicked();
    void on_btnSupprimer_clicked();
    void on_btnVider_clicked();
    void on_btnTrierPrix_clicked();
    void on_btnTrierDate_clicked();
    void on_btnExportPdf_clicked();
    void on_btnSaveQr_clicked();
    void on_inputSearch_textChanged(const QString &text);
    void on_comboFilterType_currentTextChanged(const QString &text);
    void on_tableCommandes_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
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

    // Connexion à la base de données
    void loadEmployes();
    bool addEmployeToDb(const Employe &e);
    bool updateEmployeInDb(const Employe &e);
    bool deleteEmployeFromDb(const QString &id);

    QString generateEmployeId() const;
    void updateQrForEmploye(const Employe &e);
};

#endif // MAINWINDOW_H