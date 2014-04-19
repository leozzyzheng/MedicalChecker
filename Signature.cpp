#include "Signature.h"

Signature::Signature(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent),m_pPaintImage(NULL)
{
    this->setFillColor(QColor(Qt::white));//避免使用透明区域
}

void Signature::paint(QPainter *painter)
{
    QPen pen(QColor(Qt::black));
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(0,0,10,10);
    m_pPaintImage = dynamic_cast<QImage*>(painter->device());
}
