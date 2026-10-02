#pragma once

#include <QColor>
#include <QString>
#include <QWidget>

// ---------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------

enum class Health { Sain, EnSoin, Urgent };

struct Animal {
    int     id = 0;
    QString nom;
    QString espece = QStringLiteral("Chien");   // "Chien", "Chat" or "Autre"
    QString race;
    int     age = 0;                            // years
    QString puce;
    QString vaccinal = QStringLiteral("À jour");
    QString proprietaire;
    QString telephone;
    Health  sante = Health::Sain;
};

QString healthText(Health h);
QColor  healthColor(Health h);
QString ageText(int years);
QString speciesEmoji(const QString &species);

// ---------------------------------------------------------------------------
// Health bar chart (promoted widget "StatsBars" in mainwindow.ui)
// ---------------------------------------------------------------------------

class StatsBars : public QWidget {
public:
    explicit StatsBars(QWidget *parent = nullptr);
    void setCounts(int sains, int soins, int urgents);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_sains = 0;
    int m_soins = 0;
    int m_urgents = 0;
};
