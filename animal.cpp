#include "animal.h"

#include <QPainter>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

QString healthText(Health h)
{
    switch (h) {
    case Health::Sain:   return QStringLiteral("Sain");
    case Health::EnSoin: return QStringLiteral("En soin");
    case Health::Urgent: return QStringLiteral("Urgent");
    }
    return QString();
}

QColor healthColor(Health h)
{
    switch (h) {
    case Health::Sain:   return QColor("#287554");
    case Health::EnSoin: return QColor("#B8743F");
    case Health::Urgent: return QColor("#C2455F");
    }
    return QColor("#000000");
}

QString ageText(int years)
{
    if (years <= 0) return QStringLiteral("Moins d'un an");
    if (years == 1) return QStringLiteral("1 an");
    return QStringLiteral("%1 ans").arg(years);
}

QString speciesEmoji(const QString &species)
{
    if (species == QLatin1String("Chien")) return QString::fromUtf8("\xF0\x9F\x90\xB6");  // dog
    if (species == QLatin1String("Chat"))  return QString::fromUtf8("\xF0\x9F\x90\xB1");  // cat
    return QString::fromUtf8("\xF0\x9F\x90\xBE");                                          // paw prints
}

// ---------------------------------------------------------------------------
// StatsBars
// ---------------------------------------------------------------------------

StatsBars::StatsBars(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(110);
}

void StatsBars::setCounts(int sains, int soins, int urgents)
{
    m_sains = sains;
    m_soins = soins;
    m_urgents = urgents;
    update();
}

void StatsBars::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    const int countH = 18;
    const int labelH = 20;
    const int baseY = height() - labelH;
    const int chartH = baseY - countH;

    QFont f = font();
    f.setPointSize(8);
    p.setFont(f);

    // Axes
    p.setPen(QColor("#E8D8D0"));
    p.drawLine(0, baseY, width(), baseY);
    p.drawLine(0, countH, 0, baseY);

    const int counts[3] = {m_sains, m_soins, m_urgents};
    const QColor colors[3] = {QColor("#713923"), QColor("#D9A17E"), QColor("#EF91A5")};
    const QString names[3] = {QStringLiteral("Sains"), QStringLiteral("En soin"), QStringLiteral("Urgents")};

    int maxCount = 1;
    for (int c : counts) maxCount = qMax(maxCount, c);

    const int slot = width() / 3;
    const int barW = qMin(34, slot - 12);

    for (int i = 0; i < 3; ++i) {
        const int cx = slot * i + slot / 2;
        const int h = qRound(double(counts[i]) * chartH / maxCount);

        p.setPen(Qt::NoPen);
        p.setBrush(colors[i]);
        p.drawRect(cx - barW / 2, baseY - h, barW, h);

        p.setPen(QColor("#713923"));
        p.drawText(QRect(cx - slot / 2, baseY - h - countH, slot, countH),
                   Qt::AlignCenter, QString::number(counts[i]));
        p.drawText(QRect(cx - slot / 2, baseY + 2, slot, labelH - 2),
                   Qt::AlignCenter, names[i]);
    }
}
