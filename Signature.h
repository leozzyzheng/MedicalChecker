#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPaintEngine>

class Signature : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Signature(QQuickPaintedItem *parent = 0);

    void paint(QPainter *painter);
signals:

public slots:
private:
    QImage * m_pPaintImage;
};

#endif // SIGNATURE_H
