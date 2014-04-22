#include "Signature.h"

Signature::Signature(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent),m_pPaintImage(NULL)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setFillColor(QColor(Qt::white));//避免使用透明区域
    setAcceptHoverEvents(true);

    m_pSender = new SignatureSender();

    connect(m_pSender, SIGNAL(sendFinished(QString)), this, SLOT(innerFinished(QString)));
    connect(m_pSender, SIGNAL(sendError(SignatureSender::ERROR_TYPE)), this, SLOT(innerError(SignatureSender::ERROR_TYPE)));
}

Signature::~Signature()
{
    m_pSender->deleteLater();
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

void Signature::sendImage(QString name)
{
    m_pSender->sendSigature(m_pPaintImage, name);
}

void Signature::innerError(SignatureSender::ERROR_TYPE error)
{
    QString errorString;

    if(error == SignatureSender::IMAGE_INVALID)
    {
        errorString = QString::fromLocal8Bit("Invaild image error");
    }
    else if(error == SignatureSender::NETWORK_BUSY)
    {
        errorString = QString::fromLocal8Bit("Wait for last request");
    }
    else if(error == SignatureSender::NETWORK_ERROR)
    {
        errorString = QString::fromLocal8Bit("Network error");
    }
    else if(error == SignatureSender::UNKNOW)
    {
        errorString = QString::fromLocal8Bit("Unknow error");
    }

    emit this->error(errorString);
}

void Signature::innerFinished(QString fileName)
{
    emit finished(fileName);
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
