#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPaintEngine>
#include <vector>

#include "Signature.h"

class Signature : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Signature(QQuickPaintedItem *parent = 0);

    void paint(QPainter *painter);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMoveEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);

signals:

public slots:
    void clear();
private:
    QImage * m_pPaintImage;
    std::vector<QPoint> m_vPoints;
};

#endif // SIGNATURE_H
