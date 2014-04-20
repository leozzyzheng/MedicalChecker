#include "Signature.h"

Signature::Signature(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent),m_pPaintImage(NULL)
{
    setFlag(QQuickItem::ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFillColor(QColor(Qt::white));//避免使用透明区域
}

void Signature::paint(QPainter *painter)
{
    if(m_vPoints.size() == 0)
        return;

    QPen pen(QColor(Qt::black));
    pen.setWidth(2);
    painter->setPen(pen);

    std::vector<QPoint>::iterator it = m_vPoints.begin();

    painter->drawLine(*it,*it);//绘制第一个点

    for(;it + 1 != m_vPoints.end();++it)
    {
        painter->drawLine(*it,*(it+1));
    }

    m_pPaintImage = dynamic_cast<QImage*>(painter->device());
}

void Signature::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    qDebug()<<event->button();

    m_vPoints.push_back(event->pos());
    update();

}

void Signature::mousePressEvent(QMoveEvent *event)
{
    qDebug()<<"press";
    event->accept();
}

void Signature::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"Release";
}

void Signature::wheelEvent(QWheelEvent *event)
{
    qDebug()<<"asdasd";
}

void Signature::clear()
{
    m_vPoints.clear();
    update();
}
