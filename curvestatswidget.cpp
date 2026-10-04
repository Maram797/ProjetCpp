#include "curvestatswidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QFont>
#include <QFontMetrics>
#include <algorithm>

CurveStatsWidget::CurveStatsWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(170);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Default initial data categories
    m_data["En attente"] = 3;
    m_data["Confirmée"]  = 6;
    m_data["En cours"]   = 4;
    m_data["Livrée"]     = 9;
    m_data["Annulée"]    = 1;
}

void CurveStatsWidget::updateData(const QMap<QString, int> &data)
{
    m_data = data;
    update();
}

void CurveStatsWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int w = width();
    const int h = height();

    // Background card
    QRect bgRect(0, 0, w, h);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#FFFFFF"));
    painter.drawRoundedRect(bgRect, 14, 14);

    if (m_data.isEmpty()) {
        painter.setPen(QColor("#8C7A70"));
        painter.setFont(QFont("Segoe UI", 10));
        painter.drawText(bgRect, Qt::AlignCenter, "Aucune donnée disponible");
        return;
    }

    const int leftPadding = 45;
    const int rightPadding = 35;
    const int topPadding = 35;
    const int bottomPadding = 38;

    const int plotWidth = w - leftPadding - rightPadding;
    const int plotHeight = h - topPadding - bottomPadding;

    if (plotWidth <= 0 || plotHeight <= 0) return;

    // Find max value for Y-axis scaling
    int maxVal = 1;
    for (int val : m_data.values()) {
        if (val > maxVal) maxVal = val;
    }
    // Give a bit of headroom
    int yMax = std::max(5, maxVal + 2);

    // Draw horizontal grid lines & labels
    painter.setFont(QFont("Segoe UI", 8));
    painter.setPen(QColor("#EFE6DF"));
    int numGridLines = 4;
    for (int i = 0; i <= numGridLines; ++i) {
        int y = topPadding + plotHeight - (i * plotHeight / numGridLines);
        painter.setPen(QPen(QColor("#F0E7DF"), 1, Qt::DashLine));
        painter.drawLine(leftPadding, y, leftPadding + plotWidth, y);

        int valAtLine = (yMax * i) / numGridLines;
        painter.setPen(QColor("#A68F81"));
        painter.drawText(QRect(5, y - 8, leftPadding - 10, 16), Qt::AlignRight | Qt::AlignVCenter, QString::number(valAtLine));
    }

    // Prepare point coordinates
    QList<QString> keys = m_data.keys();
    // Maintain standard logical status ordering
    QStringList order = {"En attente", "Confirmée", "En cours", "Livrée", "Annulée"};
    QVector<QPointF> points;
    QStringList activeLabels;

    int n = 0;
    for (const QString &key : order) {
        if (m_data.contains(key)) {
            activeLabels.append(key);
            n++;
        }
    }
    if (n == 0) {
        for (auto it = m_data.begin(); it != m_data.end(); ++it) {
            activeLabels.append(it.key());
            n++;
        }
    }

    for (int i = 0; i < n; ++i) {
        QString key = activeLabels[i];
        int val = m_data.value(key, 0);
        double x = (n == 1) ? (leftPadding + plotWidth / 2.0)
                            : (leftPadding + (i * plotWidth) / double(n - 1));
        double y = topPadding + plotHeight - (double(val) / yMax) * plotHeight;
        points.append(QPointF(x, y));
    }

    // Build smooth curve path using cubic Bézier
    QPainterPath curvePath;
    if (!points.isEmpty()) {
        curvePath.moveTo(points.first());
        for (int i = 0; i < points.size() - 1; ++i) {
            QPointF p0 = (i > 0) ? points[i - 1] : points[i];
            QPointF p1 = points[i];
            QPointF p2 = points[i + 1];
            QPointF p3 = (i + 2 < points.size()) ? points[i + 2] : p2;

            double dx = p2.x() - p1.x();
            QPointF ctrl1 = p1 + QPointF(dx * 0.45, (p2.y() - p0.y()) * 0.2);
            QPointF ctrl2 = p2 - QPointF(dx * 0.45, (p3.y() - p1.y()) * 0.2);
            curvePath.cubicTo(ctrl1, ctrl2, p2);
        }
    }

    // Fill area under curve with gentle pink-cream gradient
    if (!points.isEmpty()) {
        QPainterPath fillPath = curvePath;
        fillPath.lineTo(points.last().x(), topPadding + plotHeight);
        fillPath.lineTo(points.first().x(), topPadding + plotHeight);
        fillPath.closeSubpath();

        QLinearGradient grad(0, topPadding, 0, topPadding + plotHeight);
        grad.setColorAt(0.0, QColor(246, 165, 181, 140)); // #F6A5B5
        grad.setColorAt(0.7, QColor(252, 228, 232, 70));
        grad.setColorAt(1.0, QColor(255, 255, 255, 10));
        painter.setPen(Qt::NoPen);
        painter.setBrush(grad);
        painter.drawPath(fillPath);
    }

    // Draw the curve line
    QPen linePen(QColor("#633927"), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(linePen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(curvePath);

    // Draw data points and value badges
    for (int i = 0; i < points.size(); ++i) {
        QPointF pt = points[i];
        int val = m_data.value(activeLabels[i], 0);

        // Point outer circle
        painter.setPen(QPen(QColor("#633927"), 2));
        painter.setBrush(QColor("#F6A5B5"));
        painter.drawEllipse(pt, 5.5, 5.5);

        // Point inner dot
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#FFFFFF"));
        painter.drawEllipse(pt, 2.5, 2.5);

        // Value text above point
        painter.setPen(QColor("#633927"));
        painter.setFont(QFont("Segoe UI", 8, QFont::Bold));
        painter.drawText(QRectF(pt.x() - 15, pt.y() - 20, 30, 16), Qt::AlignCenter, QString::number(val));

        // X-axis label
        painter.setPen(QColor("#7D6658"));
        painter.setFont(QFont("Segoe UI", 8));
        painter.drawText(QRectF(pt.x() - 40, topPadding + plotHeight + 6, 80, 24), Qt::AlignHCenter | Qt::AlignTop, activeLabels[i]);
    }
}
