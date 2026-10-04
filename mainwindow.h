#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Fournisseur
{
    QString id;
    QString nom;
    QString prenom;
    QString telephone;
    QString mail;
};

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
    QList<Fournisseur> m_fournisseurs;
    bool m_sortAscNom;
    bool m_sortAscPrenom;

    void refreshTable();
    void updateStatistics();
    void clearForm();
    QList<Fournisseur> currentFilteredList() const;
    int fournisseurIndex(const QString &id) const;
    Fournisseur fournisseurFromForm() const;
    bool formIsValid();
    void saveFournisseurs() const;
    void loadFournisseurs();
};

#endif // MAINWINDOW_H
