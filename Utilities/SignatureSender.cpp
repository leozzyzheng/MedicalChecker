#include "SignatureSender.h"

SignatureSender::SignatureSender(QObject *parent) :
    QObject(parent),m_pCurrentReply(NULL)
{
    m_pNetMgr = new QNetworkAccessManager();

    connect(m_pNetMgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));

    m_pThread = ThreadSingleton::getInstance();
    moveToThread(m_pThread);
}

void SignatureSender::sendSigature(QImage * image, QString name)
{
    if(m_pCurrentReply && m_pCurrentReply->isRunning())
    {
        emit sendError(NETWORK_BUSY);
        return;
    }

    if(!image || image->isNull())
    {
        emit sendError(IMAGE_INVALID);
        return;
    }

    QImage copy = image->convertToFormat(QImage::Format_Mono);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadWrite);
    copy.save(&buffer, "PNG"); // writes image into ba in PNG format
    buffer.close();

    QString temp = QString("--") + BOUNDARY + "\r\nContent-Disposition: form-data; name=\"" + NAME + "\"; filename=\""+name+"\"";
    temp += "\r\nContent-Type: image/png\r\n\r\n";
    ba = temp.toUtf8() + ba;
    ba = ba.append("\r\n--").append(BOUNDARY).append("--\r\n");


    QNetworkRequest request(QUrl("http://192.168.0.102:8888/Clinic/signUpload.action"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("multipart/form-data; boundary=") + BOUNDARY);
    request.setHeader(QNetworkRequest::ContentLengthHeader, ba.length());
    m_pCurrentReply = m_pNetMgr->post(request , ba);

    connect(m_pCurrentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(innerError(QNetworkReply::NetworkError)));
    connect(m_pCurrentReply, SIGNAL(uploadProgress ( qint64 ,qint64 )),  this, SIGNAL(progress(qint64 ,qint64 )));
}

void SignatureSender::replyFinished(QNetworkReply *pReply)
{
    disconnect(m_pCurrentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(innerError(QNetworkReply::NetworkError)));
    disconnect(m_pCurrentReply, SIGNAL(uploadProgress ( qint64 ,qint64 )),  this, SIGNAL(progress(qint64 ,qint64 )));
    QString respone = pReply->readAll();
    qDebug()<<"Send Finished:"<<respone;
    emit sendFinished(respone);
}

void SignatureSender::innerError(QNetworkReply::NetworkError err)
{
    qDebug()<<"Send error:"<<err;
    emit sendError(NETWORK_ERROR);
}
