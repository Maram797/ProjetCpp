#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QHash>

class QEvent;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void setNavigationButton(QWidget *button);
    void filterProducts();
    void sortProductsByPrice();
    void clearProductForm();
    void refreshStatistics();

    Ui::MainWindow *ui;
    QList<QWidget*> navigationButtons;
    QHash<QWidget*, QString> normalButtonStyles;
    QString activeButtonStyle;
};
#endif // MAINWINDOW_H
