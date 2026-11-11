#ifndef STOCKDIALOG_H
#define STOCKDIALOG_H

#include <QDialog>

class QLineEdit;
class QTableWidget;

class StockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StockDialog(QWidget *parent = nullptr);

private slots:
    void loadProducts();
    void addProduct();
    void updateProduct();
    void deleteProduct();
    void selectProduct(int row, int column);

private:
    QLineEdit *m_idEdit;
    QLineEdit *m_designationEdit;
    QLineEdit *m_productEdit;
    QLineEdit *m_categoryEdit;
    QLineEdit *m_quantityEdit;
    QLineEdit *m_priceEdit;
    QTableWidget *m_table;
    int m_selectedId;

    bool readForm(QString &designation, QString &product, QString &category,
                  int &quantity, double &price);
};

#endif
