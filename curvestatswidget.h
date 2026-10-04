#ifndef CURVESTATSWIDGET_H
#define CURVESTATSWIDGET_H

#include <QWidget>
#include <QMap>
#include <QString>

class CurveStatsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CurveStatsWidget(QWidget *parent = nullptr);
    void updateData(const QMap<QString, int> &data);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, int> m_data;
};

#endif // CURVESTATSWIDGET_H
