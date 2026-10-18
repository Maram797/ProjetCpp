#ifndef QRCODEGENERATOR_H
#define QRCODEGENERATOR_H

#include <QPixmap>
#include <QString>

class QRCodeGenerator
{
public:
    static QPixmap generate(const QString &data);
};

#endif // QRCODEGENERATOR_H