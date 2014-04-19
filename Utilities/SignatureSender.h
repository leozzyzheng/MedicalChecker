//签名的二值图发送类
//由于网络字节使用的是big endian的字节序列,所以图像二值化之后使用的是MSB存储方式
//网络传输使用阻塞式,一次只能传输一个图片

#ifndef SIGNATURESENDER_H
#define SIGNATURESENDER_H

#include <QObject>
#include <QImage>
#include <QBuffer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "ThreadSingleton.h"

class SignatureSender : public QObject
{
    Q_OBJECT
public:
    enum ERROR_TYPE
    {
        IMAGE_INVALID,
        NETWORK_ERROR,
        NETWORK_BUSY
    };

    explicit SignatureSender(QObject *parent = 0);

signals:
    void error(ERROR_TYPE err);
    void progress(qint64 ,qint64);
    void finished(QString responseText);

public slots:
    void sendSigature(QImage & image);

private slots:
    void replyFinished(QNetworkReply * pReply);
    void innerError(QNetworkReply::NetworkError);
private:
    QThread * m_pThread;
    QNetworkAccessManager * m_pNetMgr;
    QNetworkReply * m_pCurrentReply;
};

#endif // SIGNATURESENDER_H
