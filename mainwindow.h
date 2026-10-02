#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

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
    void on_btn_ajouter_clicked();
    void on_btn_modifier_clicked();
    void on_btn_vider_clicked();
    void on_btn_enregistrer_clicked();
    void on_comboBox_tri_currentIndexChanged(int index);
    void on_lineEdit_recherche_textChanged(const QString &text);
    void on_btn_exporter_pdf_clicked();
    void on_tableWidget_commandes_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    void chargerCommandes();
    void sauvegarderCommandes();
    void afficherStatistiques();
};
#endif // MAINWINDOW_H