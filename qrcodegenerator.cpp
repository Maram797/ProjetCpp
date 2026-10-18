#include "qrcodegenerator.h"
#include <QImage>
#include <QPainter>
#include <qrencode.h>

QPixmap QRCodeGenerator::generate(const QString &data)
{
    QRcode *qr = QRcode_encodeString(data.toUtf8().constData(), 0, QR_ECLEVEL_M, QR_MODE_8, 1);
    if (!qr) return QPixmap();

    const int scale = 6;
    const int size  = qr->width * scale;
    QImage img(size, size, QImage::Format_RGB32);
    img.fill(Qt::white);

    QPainter p(&img);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    for (int y = 0; y < qr->width; ++y) {
        for (int x = 0; x < qr->width; ++x) {
            if (qr->data[y * qr->width + x] & 1)
                p.drawRect(x * scale, y * scale, scale, scale);
        }
    }
    p.end();
    QRcode_free(qr);

    return QPixmap::fromImage(img);
}