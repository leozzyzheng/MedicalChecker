#include "Signature.h"

Signature::Signature(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent),m_pPaintImage(NULL)
{
    setFlag(QQuickItem::ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod,true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFillColor(QColor(Qt::white));//避免使用透明区域
    setAcceptHoverEvents(true);
}

void Signature::paint(QPainter *painter)
{
    if(m_vPoints.size() == 0 && m_vCurrentPoints.size() == 0)
        return;

    QPen pen(QColor(Qt::black));
    pen.setWidth(2);
    painter->setPen(pen);

    std::vector< std::vector<QPoint> >::iterator itAll = m_vPoints.begin();

    for(; itAll != m_vPoints.end(); ++itAll)
    {
        paintVecPoint(painter, *itAll);
    }

    paintVecPoint(painter, m_vCurrentPoints);

    m_pPaintImage = dynamic_cast<QImage*>(painter->device());
}

void Signature::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    m_vCurrentPoints.push_back(event->pos());
    update();
}

void Signature::mousePressEvent(QMouseEvent *event)
{
    m_vCurrentPoints.clear();
    qDebug()<<"press";
    event->accept();
}

void Signature::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    qDebug()<<"Release";
    std::vector<QPoint> copy = m_vCurrentPoints;
    m_vPoints.push_back(copy);
    m_vCurrentPoints.clear();
    update();
}

void Signature::clearImage()
{
    m_vPoints.clear();
    m_vCurrentPoints.clear();
    update();
}

void Signature::paintVecPoint(QPainter *painter, std::vector<QPoint> &points)
{
    if(points.size() == 0)
        return;

    std::vector<QPoint>::iterator it = points.begin();

    painter->drawLine(*it,*it);//绘制第一个点

    for(;it + 1 != points.end();++it)
    {
        painter->drawLine(*it,*(it+1));
    }
}
