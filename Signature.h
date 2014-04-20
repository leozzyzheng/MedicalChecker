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
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
signals:

public slots:
    void clearImage();
private:
    void paintVecPoint(QPainter* painter, std::vector<QPoint> & points);

    QImage * m_pPaintImage;
    std::vector< std::vector<QPoint> > m_vPoints;
    std::vector<QPoint> m_vCurrentPoints;
};

#endif // SIGNATURE_H
