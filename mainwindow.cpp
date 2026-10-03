#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QEvent>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QPixmap>
#include <QTextStream>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFrame>
#include <QMouseEvent>
#include <algorithm>
#include <QMap>
#include <QtMath>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->logo->setPixmap(QPixmap(":/images/logo.jpeg"));
    ui->logo->setScaledContents(true);

    // Les prix sont enregistrés comme valeurs numériques afin que le tri
    // respecte 74,900 > 42,500 > 36,900 > 32,800.
    for (int row = 0; row < ui->ExListe->rowCount(); ++row) {
        if (auto *price = ui->ExListe->item(row, 3)) {
            QString value = price->text().remove(" ").replace(',', '.');
            price->setData(Qt::UserRole, value.toDouble());
        }
    }
    // L'affichage initial est volontairement désordonné.
    for (int top = 0, bottom = ui->ExListe->rowCount() - 1; top < bottom; ++top, --bottom) {
        for (int column = 0; column < ui->ExListe->columnCount(); ++column) {
            QTableWidgetItem *first = ui->ExListe->takeItem(top, column);
            QTableWidgetItem *last = ui->ExListe->takeItem(bottom, column);
            ui->ExListe->setItem(top, column, last);
            ui->ExListe->setItem(bottom, column, first);
        }
    }

    navigationButtons = {ui->Banimaux, ui->Bpropritaires, ui->Brendezvous,
                         ui->Bstocks, ui->Bpaiements};
    activeButtonStyle = ui->Bstocks->styleSheet();
    // Bstocks est brun lorsqu'il représente la section active, mais reprend
    // le style des boutons ordinaires lorsqu'une autre section est sélectionnée.
    normalButtonStyles.insert(ui->Bstocks, ui->Bpaiements->styleSheet());
    for (QWidget *button : navigationButtons) {
        normalButtonStyles.insert(button, button->styleSheet());
        button->installEventFilter(this);
        connect(static_cast<QPushButton*>(button), &QPushButton::clicked,
                this, [this, button] { setNavigationButton(button); });
    }
    setNavigationButton(ui->Bstocks);

    ui->FormulaireProduit->setVisible(false);
    ui->ExListe->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ExListe->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->ExListe, &QTableWidget::cellClicked, this,
            [this](int row, int) { loadProductIntoForm(row); });
    ui->Bnouveau->installEventFilter(this);
    ui->Bparametre->installEventFilter(this);
    ui->Baide->installEventFilter(this);
    normalButtonStyles.insert(ui->Bnouveau, ui->Bnouveau->styleSheet());
    normalButtonStyles.insert(ui->Bparametre, ui->Bparametre->styleSheet());
    normalButtonStyles.insert(ui->Baide, ui->Baide->styleSheet());
    ui->Recherche->setStyleSheet(ui->Recherche->styleSheet() + "\ncolor: black;");
    ui->Bparametre->setMinimumSize(120, 42);
    ui->Baide->setMinimumSize(90, 42);
    connect(ui->Bnouveau, &QPushButton::clicked, this, [this] {
        const bool visible = !ui->FormulaireProduit->isVisible();
        ui->FormulaireProduit->setVisible(visible);
        if (visible) {
            selectedProductRow = -1;
            clearProductForm();
        }
        ui->Bnouveau->setProperty("active", visible);
        ui->Bnouveau->setStyleSheet(visible ? activeButtonStyle
                                            : normalButtonStyles.value(ui->Bnouveau));
        if (visible) ui->ExNom->setFocus();
    });
    connect(ui->Recherche, &QLineEdit::textChanged, this, &MainWindow::filterProducts);
    connect(ui->Categorie, &QComboBox::currentTextChanged, this, &MainWindow::filterProducts);
    connect(ui->Btrier, &QPushButton::clicked, this, [this] {
        sortProductsByPrice();
    });
    connect(ui->Btrier_4, &QPushButton::clicked, this, [this] {
        sortProductsByPrice();
    });
    connect(ui->Bexporter, &QPushButton::clicked, this, [this] {
        const QString path = QFileDialog::getSaveFileName(this, tr("Exporter les produits"),
                                                           QString(), tr("CSV (*.csv)"));
        if (path.isEmpty()) return;
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&file);
        for (int c = 0; c < ui->ExListe->columnCount(); ++c) {
            if (c) out << ';';
            out << ui->ExListe->horizontalHeaderItem(c)->text();
        }
        out << '\n';
        for (int r = 0; r < ui->ExListe->rowCount(); ++r) {
            if (ui->ExListe->isRowHidden(r)) continue;
            for (int c = 0; c < ui->ExListe->columnCount(); ++c) {
                if (c) out << ';';
                out << ui->ExListe->item(r, c)->text();
            }
            out << '\n';
        }
        QMessageBox::information(this, tr("Exportation"), tr("Les produits ont été exportés."));
    });
    connect(ui->Bvider, &QPushButton::clicked, this, &MainWindow::clearProductForm);
    connect(ui->Benragister, &QPushButton::clicked, this, &MainWindow::saveProductFromForm);
    connect(ui->Bconseil, &QPushButton::clicked, this, [this] {
        QMessageBox::information(this, tr("Conseil automatique"),
                                 tr("Pensez à réapprovisionner les produits en rupture ou en stock faible."));
    });
    connect(ui->Bparametre, &QLabel::linkActivated, this, [] {});
    ui->Bparametre->setCursor(Qt::PointingHandCursor);
    ui->Baide->setCursor(Qt::PointingHandCursor);
    refreshStatistics();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    // Le formulaire garde toujours son style défini dans Qt Designer.
    if (watched == ui->Bparametre && event->type() == QEvent::MouseButtonRelease)
        QMessageBox::information(this, tr("Paramètres"), tr("Les paramètres seront disponibles dans cette section."));
    if (watched == ui->Baide && event->type() == QEvent::MouseButtonRelease)
        QMessageBox::information(this, tr("Aide"), tr("Utilisez Nouveau pour ajouter un produit, puis Enregistrer."));
    if (event->type() == QEvent::Enter) {
        if (auto *button = qobject_cast<QWidget*>(watched)) {
            if (button == ui->FormulaireProduit) return false;
            button->setProperty("active", true);
            button->setStyleSheet(activeButtonStyle);
        }
    } else if (event->type() == QEvent::Leave) {
        if (auto *button = qobject_cast<QWidget*>(watched)) {
            if (button == ui->FormulaireProduit) return false;
            if (watched != ui->Bnouveau && watched != ui->FormulaireProduit)
                button->setProperty("active", false);
            if (watched != ui->Bnouveau && watched != ui->FormulaireProduit)
                button->setStyleSheet(normalButtonStyles.value(button));
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::setNavigationButton(QWidget *button)
{
    for (QWidget *item : navigationButtons) {
        item->setProperty("active", item == button);
        item->setStyleSheet(item == button ? activeButtonStyle : normalButtonStyles.value(item));
    }
}

void MainWindow::filterProducts()
{
    auto normalized = [](QString value) {
        value = value.trimmed().toLower();
        if (value == "tous" || value == "tout") return value;
        if (value.endsWith('s')) value.chop(1);
        return value;
    };
    auto categoryKey = [](QString value) {
        value = value.trimmed().toLower();
        if (value.startsWith("aliment")) return QString("alimentation");
        if (value.startsWith("soin")) return QString("soin");
        if (value.startsWith("access")) return QString("accessoire");
        return value;
    };
    const QString query = normalized(ui->Recherche->text());
    const QString queryCategory = categoryKey(ui->Recherche->text());
    const QString category = categoryKey(ui->Categorie->currentText());
    for (int r = 0; r < ui->ExListe->rowCount(); ++r) {
        const QString product = normalized(ui->ExListe->item(r, 0)->text());
        const QString productCategory = categoryKey(ui->ExListe->item(r, 1)->text());
        const bool showAll = query.isEmpty() || query == "tout" || query == "tous";
        const bool alimentationMatch = query.contains("aliment")
            && ui->ExListe->item(r, 1)->text().trimmed().toLower().contains("aliment");
        const bool categoryTextMatch = alimentationMatch || productCategory == queryCategory
            || productCategory.contains(query) || queryCategory.contains(productCategory);
        const bool textMatch = showAll || product.contains(query) || categoryTextMatch;
        const bool allCategories = category.isEmpty() || category == "tout" || category == "tous";
        const QString rawCategory = ui->ExListe->item(r, 1)->text().trimmed().toLower();
        const bool categoryMatch = allCategories || productCategory == category
            || (category.startsWith("aliment") && rawCategory.contains("aliment"));
        ui->ExListe->setRowHidden(r, !(textMatch && categoryMatch));
    }
}

void MainWindow::sortProductsByPrice()
{
    struct ProductRow { double price; QList<QTableWidgetItem*> cells; };
    QList<ProductRow> rows;
    while (ui->ExListe->rowCount() > 0) {
        const int row = ui->ExListe->rowCount() - 1;
        ProductRow product;
        product.price = ui->ExListe->item(row, 3)->text().remove(" ").replace(',', '.').toDouble();
        for (int column = 0; column < ui->ExListe->columnCount(); ++column)
            product.cells.append(ui->ExListe->takeItem(row, column));
        ui->ExListe->removeRow(row);
        rows.append(product);
    }
    std::sort(rows.begin(), rows.end(), [](const ProductRow &a, const ProductRow &b) {
        return a.price > b.price;
    });
    for (const ProductRow &product : rows) {
        const int row = ui->ExListe->rowCount();
        ui->ExListe->insertRow(row);
        for (int column = 0; column < product.cells.size(); ++column)
            ui->ExListe->setItem(row, column, product.cells.at(column));
    }
    filterProducts();
}

void MainWindow::clearProductForm()
{
    ui->Exid->clear(); ui->ExNom->clear(); ui->ExDesignation->clear();
    ui->ExQuantite->setValue(0); ui->ExPrix->setValue(0.0);
}

void MainWindow::loadProductIntoForm(int row)
{
    selectedProductRow = row;
    ui->Exid->setText(ui->ExListe->item(row, 0)->data(Qt::UserRole + 1).toString());
    ui->ExNom->setText(ui->ExListe->item(row, 0)->text());
    ui->Excategorie->setCurrentText(ui->ExListe->item(row, 1)->text());
    ui->ExQuantite->setValue(ui->ExListe->item(row, 2)->text().toInt());
    ui->ExPrix->setValue(ui->ExListe->item(row, 3)->text().replace(',', '.').toDouble());
    ui->ExDesignation->setText(ui->ExListe->item(row, 0)->data(Qt::UserRole + 2).toString());
    if (!ui->FormulaireProduit->isVisible()) {
        ui->FormulaireProduit->setVisible(true);
        ui->Bnouveau->setProperty("active", true);
        ui->Bnouveau->setStyleSheet(activeButtonStyle);
    }
}

void MainWindow::saveProductFromForm()
{
    const QString name = ui->ExNom->text().trimmed();
    if (name.isEmpty() && selectedProductRow >= 0) {
        ui->ExListe->removeRow(selectedProductRow);
        selectedProductRow = -1;
        clearProductForm();
        refreshStatistics();
        filterProducts();
        return;
    }
    if (name.isEmpty()) {
        QMessageBox::warning(this, tr("Formulaire"), tr("Le nom du produit est obligatoire."));
        return;
    }
    const int row = selectedProductRow >= 0 ? selectedProductRow : ui->ExListe->rowCount();
    if (selectedProductRow < 0) ui->ExListe->insertRow(row);
    auto *nameItem = new QTableWidgetItem(name);
    nameItem->setData(Qt::UserRole + 1, ui->Exid->text());
    nameItem->setData(Qt::UserRole + 2, ui->ExDesignation->text());
    ui->ExListe->setItem(row, 0, nameItem);
    ui->ExListe->setItem(row, 1, new QTableWidgetItem(ui->Excategorie->currentText()));
    ui->ExListe->setItem(row, 2, new QTableWidgetItem(QString::number(ui->ExQuantite->value())));
    ui->ExListe->setItem(row, 3, new QTableWidgetItem(QString::number(ui->ExPrix->value(), 'f', 3)));
    const QString availability = selectedProductRow < 0
        ? tr("En stock")
        : (ui->ExQuantite->value() == 0 ? tr("Rupture") : tr("En stock"));
    ui->ExListe->setItem(row, 4, new QTableWidgetItem(availability));
    selectedProductRow = -1;
    clearProductForm();
    refreshStatistics();
    filterProducts();
}

void MainWindow::refreshStatistics()
{
    QMap<QString, int> counts;
    for (int row = 0; row < ui->ExListe->rowCount(); ++row)
        counts[ui->ExListe->item(row, 1)->text().trimmed()]++;
    QString bestCategory;
    int bestCount = 0;
    for (auto it = counts.cbegin(); it != counts.cend(); ++it) {
        if (it.value() > bestCount) { bestCategory = it.key(); bestCount = it.value(); }
    }
    const int total = ui->ExListe->rowCount();
    const int percentage = total ? qRound(100.0 * bestCount / total) : 0;
    ui->produitdisponible->setText(tr("   ● %1% des produits sont des %2").arg(percentage).arg(bestCategory.isEmpty() ? tr("produits") : bestCategory));
    const QStringList categories = {tr("Alim."), tr("Soin"), tr("Access.")};
    const QStringList categoryKeys = {tr("Alimentation"), tr("Soin"), tr("Accessoire")};
    const QList<QPushButton*> labels = {ui->Btrier_2, ui->Btrier_5, ui->Btrier_4};
    const QList<QFrame*> bars = {ui->frame_5, ui->frame_4, ui->frame_6};
    for (int i = 0; i < labels.size(); ++i)
    {
        const int percent = total ? qRound(100.0 * counts.value(categoryKeys[i]) / total) : 0;
        QFont font = labels[i]->font();
        font.setPointSize(8);
        labels[i]->setFont(font);
        labels[i]->setText(QString("%1\n%2%").arg(categories[i]).arg(percent));
        const int height = qMax(2, qRound(130.0 * percent / 100.0));
        QRect geometry = bars[i]->geometry();
        geometry.setY(190 - height);
        geometry.setHeight(height);
        bars[i]->setGeometry(geometry);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
