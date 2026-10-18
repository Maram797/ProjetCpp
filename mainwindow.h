#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "animal.h"

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushbutton_ajouter_clicked();
    void on_pushbutton_supprimer_clicked();
    void on_pushbutton_trierdate_clicked();
    void on_pushbutton_exporterpdf_clicked();
    void on_btnmodifier_clicked();
    void on_btnnouvelanimal_clicked();
    void on_btnannuler_clicked();
    void on_tableanimaux_selectionChanged();
    void on_editrecherche_textChanged();
    void on_editfiltre_textChanged();

private:
    void actualiserAffichage();
    void chargerTableDepuisModele(QSqlQueryModel *model);
    void exporterEnPdf();
    int selectedId() const;
    QString filterText() const;
    QString phoneDigits() const;
    void showList();
    void clearForm();

    Ui::MainWindow *ui;
    Animal Etmp;
    int m_editId = 0;
    bool m_sortAsc = true;
};

#endif 
