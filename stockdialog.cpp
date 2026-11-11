#include "stockdialog.h"

#include <QDoubleValidator>
#include <QFormLayout>
#include <QHeaderView>
#include <QIntValidator>
#include <QLineEdit>
#include <QLocale>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QTableWidget>
#include <QVBoxLayout>

namespace {
const QString stocksTable = "\"PAWCHE_2\".\"STOCKS\"";
}

StockDialog::StockDialog(QWidget *parent)
    : QDialog(parent), m_idEdit(new QLineEdit(this)),
      m_designationEdit(new QLineEdit(this)), m_productEdit(new QLineEdit(this)),
      m_categoryEdit(new QLineEdit(this)), m_quantityEdit(new QLineEdit(this)),
      m_priceEdit(new QLineEdit(this)), m_table(new QTableWidget(this)),
      m_selectedId(-1)
{
    setWindowTitle("Gestion des stocks");
    resize(900, 560);

    m_idEdit->setReadOnly(true);
    m_quantityEdit->setValidator(new QIntValidator(0, 2147483647, m_quantityEdit));
    auto *priceValidator = new QDoubleValidator(0, 999999999, 3, m_priceEdit);
    priceValidator->setLocale(QLocale::c());
    m_priceEdit->setValidator(priceValidator);

    auto *form = new QFormLayout;
    form->addRow("ID", m_idEdit);
    form->addRow("Désignation", m_designationEdit);
    form->addRow("Produit", m_productEdit);
    form->addRow("Catégorie", m_categoryEdit);
    form->addRow("Quantité", m_quantityEdit);
    form->addRow("Prix", m_priceEdit);

    auto *addButton = new QPushButton("Ajouter", this);
    auto *updateButton = new QPushButton("Modifier", this);
    auto *deleteButton = new QPushButton("Supprimer", this);
    auto *clearButton = new QPushButton("Vider", this);
    auto *reloadButton = new QPushButton("Actualiser", this);

    auto *buttons = new QHBoxLayout;
    buttons->addWidget(addButton);
    buttons->addWidget(updateButton);
    buttons->addWidget(deleteButton);
    buttons->addWidget(clearButton);
    buttons->addWidget(reloadButton);

    m_table->setColumnCount(6);
    m_table->setHorizontalHeaderLabels(
        {"ID", "Désignation", "Produit", "Catégorie", "Quantité", "Prix"});
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addLayout(buttons);
    layout->addWidget(m_table);

    connect(addButton, &QPushButton::clicked, this, &StockDialog::addProduct);
    connect(updateButton, &QPushButton::clicked, this, &StockDialog::updateProduct);
    connect(deleteButton, &QPushButton::clicked, this, &StockDialog::deleteProduct);
    connect(clearButton, &QPushButton::clicked, this, [this] {
        m_table->clearSelection();
        m_selectedId = -1;
        m_designationEdit->clear();
        m_productEdit->clear();
        m_categoryEdit->clear();
        m_quantityEdit->clear();
        m_priceEdit->clear();
        m_productEdit->setFocus();
    });
    connect(reloadButton, &QPushButton::clicked, this, &StockDialog::loadProducts);
    connect(m_table, &QTableWidget::cellClicked,
            this, &StockDialog::selectProduct);

    loadProducts();
}

void StockDialog::loadProducts()
{
    QSqlQuery query;
    const QString sql = QString("SELECT IDP, DESIGNATION, PRODUIT, CATEGORIE, "
                                "QUANTITE, PRIX FROM %1 ORDER BY IDP")
                            .arg(stocksTable);
    if (!query.exec(sql)) {
        QMessageBox::critical(this, "Base de données",
                              "Impossible de charger les produits depuis Oracle :\n"
                                  + query.lastError().text());
        return;
    }

    m_table->setRowCount(0);
    while (query.next()) {
        const int row = m_table->rowCount();
        m_table->insertRow(row);
        for (int column = 0; column < 6; ++column)
            m_table->setItem(row, column,
                             new QTableWidgetItem(query.value(column).toString()));
    }

    QSqlQuery idQuery;
    if (!idQuery.exec(QString("SELECT NVL(MAX(IDP), 0) + 1 FROM %1").arg(stocksTable))) {
        QMessageBox::critical(this, "Base de données",
                              "Impossible de générer un identifiant produit :\n"
                                  + idQuery.lastError().text());
        return;
    }
    if (idQuery.next())
        m_idEdit->setText(idQuery.value(0).toString());
}

bool StockDialog::readForm(QString &designation, QString &product, QString &category,
                           int &quantity, double &price)
{
    designation = m_designationEdit->text().trimmed();
    product = m_productEdit->text().trimmed();
    category = m_categoryEdit->text().trimmed();
    bool quantityOk = false;
    bool priceOk = false;
    quantity = m_quantityEdit->text().toInt(&quantityOk);
    price = QLocale::c().toDouble(m_priceEdit->text(), &priceOk);

    if (designation.isEmpty() || product.isEmpty() || category.isEmpty() ||
        m_quantityEdit->text().isEmpty() || m_priceEdit->text().isEmpty() ||
        !quantityOk || !priceOk || quantity < 0 || price < 0) {
        QMessageBox::warning(this, "Champs invalides",
                             "Remplissez tous les champs avec une quantité et un prix positifs.");
        return false;
    }

    if (designation.toUtf8().size() > 100 || product.toUtf8().size() > 150 ||
        category.toUtf8().size() > 100) {
        QMessageBox::warning(this, "Valeur trop longue",
                             "Limites : désignation 100 caractères, produit 150, catégorie 100.");
        return false;
    }
    return true;
}

void StockDialog::addProduct()
{
    bool idOk = false;
    const int id = m_idEdit->text().toInt(&idOk);
    if (!idOk || id < 0) {
        QMessageBox::warning(this, "Identifiant invalide",
                             "Impossible de générer un identifiant produit.");
        return;
    }

    QString designation, product, category;
    int quantity = 0;
    double price = 0;
    if (!readForm(designation, product, category, quantity, price))
        return;

    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1 "
                          "(IDP, DESIGNATION, PRODUIT, CATEGORIE, QUANTITE, PRIX) "
                          "VALUES (:id, :designation, :product, :category, :quantity, :price)")
                      .arg(stocksTable));
    query.bindValue(":id", id);
    query.bindValue(":designation", designation);
    query.bindValue(":product", product);
    query.bindValue(":category", category);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    if (!query.exec()) {
        QMessageBox::critical(this, "Base de données",
                              "Impossible d'ajouter le produit :\n"
                                  + query.lastError().text());
        return;
    }

    loadProducts();
    m_designationEdit->clear();
    m_productEdit->clear();
    m_categoryEdit->clear();
    m_quantityEdit->clear();
    m_priceEdit->clear();
    m_selectedId = -1;
    QMessageBox::information(this, "Succès", "Produit ajouté dans la base de données.");
}

void StockDialog::updateProduct()
{
    if (m_selectedId < 0) {
        QMessageBox::warning(this, "Sélection requise", "Sélectionnez un produit à modifier.");
        return;
    }

    QString designation, product, category;
    int quantity = 0;
    double price = 0;
    if (!readForm(designation, product, category, quantity, price))
        return;

    QSqlQuery query;
    query.prepare(QString("UPDATE %1 SET DESIGNATION=:designation, PRODUIT=:product, "
                          "CATEGORIE=:category, QUANTITE=:quantity, PRIX=:price WHERE IDP=:id")
                      .arg(stocksTable));
    query.bindValue(":designation", designation);
    query.bindValue(":product", product);
    query.bindValue(":category", category);
    query.bindValue(":quantity", quantity);
    query.bindValue(":price", price);
    query.bindValue(":id", m_selectedId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Base de données",
                              "Impossible de modifier le produit :\n"
                                  + query.lastError().text());
        return;
    }
    loadProducts();
    QMessageBox::information(this, "Succès", "Produit modifié dans la base de données.");
}

void StockDialog::deleteProduct()
{
    if (m_selectedId < 0) {
        QMessageBox::warning(this, "Sélection requise", "Sélectionnez un produit à supprimer.");
        return;
    }
    if (QMessageBox::question(this, "Confirmation", "Supprimer ce produit ?")
        != QMessageBox::Yes)
        return;

    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE IDP=:id").arg(stocksTable));
    query.bindValue(":id", m_selectedId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Base de données",
                              "Impossible de supprimer le produit :\n"
                                  + query.lastError().text());
        return;
    }
    m_selectedId = -1;
    loadProducts();
    QMessageBox::information(this, "Succès", "Produit supprimé de la base de données.");
}

void StockDialog::selectProduct(int row, int)
{
    if (row < 0 || !m_table->item(row, 0))
        return;
    m_selectedId = m_table->item(row, 0)->text().toInt();
    m_idEdit->setText(QString::number(m_selectedId));
    m_designationEdit->setText(m_table->item(row, 1)->text());
    m_productEdit->setText(m_table->item(row, 2)->text());
    m_categoryEdit->setText(m_table->item(row, 3)->text());
    m_quantityEdit->setText(m_table->item(row, 4)->text());
    m_priceEdit->setText(m_table->item(row, 5)->text());
}
