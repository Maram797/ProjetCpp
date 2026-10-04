#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "commande.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void on_inputSearch_textChanged(const QString &text);
    void on_comboFilterType_currentTextChanged(const QString &text);
    void on_tableCommandes_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QList<Commande> m_commandes;
    bool m_sortAscPrix;
    bool m_sortAscDate;

    void loadSampleData();
    void refreshTable(const QList<Commande> &list);
    void updateStatistics();
    void clearForm();
    QList<Commande> currentFilteredList() const;
};

#endif // MAINWINDOW_H
