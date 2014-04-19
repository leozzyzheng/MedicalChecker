#include "SignatureSender.h"

SignatureSender::SignatureSender(QObject *parent) :
    QObject(parent),m_pCurrentReply(NULL)
{
    m_pNetMgr = new QNetworkAccessManager();

    connect(m_pNetMgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));

    m_pThread = ThreadSingleton::getInstance();
    moveToThread(m_pThread);
}

void SignatureSender::sendSigature(QImage &image)
{
    if(m_pCurrentReply && m_pCurrentReply->isRunning())
    {
        emit error(NETWORK_BUSY);
        return;
    }

    if(image.isNull())
    {
        emit error(IMAGE_INVALID);
        return;
    }

    QImage copy = image.convertToFormat(QImage::Format_Mono);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadWrite);
    copy.save(&buffer, "PNG"); // writes image into ba in PNG format
    buffer.close();

    QNetworkRequest request(QUrl("http://localhost/up.php?act=up&filename=a.jpg"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    m_pCurrentReply = m_pNetMgr->post(request , ba);

    connect(m_pCurrentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(innerError(QNetworkReply::NetworkError)));
    connect(m_pCurrentReply, SIGNAL(uploadProgress ( qint64 ,qint64 )),  this, SIGNAL(progress(qint64 ,qint64 )));
}

void SignatureSender::replyFinished(QNetworkReply *pReply)
{
    disconnect(m_pCurrentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(innerError(QNetworkReply::NetworkError)));
    disconnect(m_pCurrentReply, SIGNAL(uploadProgress ( qint64 ,qint64 )),  this, SIGNAL(progress(qint64 ,qint64 )));
    emit finished(pReply->readAll());
}

void SignatureSender::innerError(QNetworkReply::NetworkError)
{
    emit error(NETWORK_ERROR);
}
