#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPaintEngine>
#include <vector>

#include "Signature.h"
#include "Utilities/SignatureSender.h"
#include "Utilities/GlobalHelper.h"

class Signature : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Signature(QQuickPaintedItem *parent = 0);
    ~Signature();

    void paint(QPainter *painter);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
signals:
    void finished(QString fileName);
    void error(QString error);
public slots:
    Q_INVOKABLE void clearImage();
    Q_INVOKABLE void sendImage();
private slots:
    void innerError(SignatureSender::ERROR_TYPE error);
    void innerFinished(QString fileName);
private:
    void paintVecPoint(QPainter* painter, std::vector<QPoint> & points);
    QImage * m_pPaintImage;
    std::vector< std::vector<QPoint> > m_vPoints;
    std::vector<QPoint> m_vCurrentPoints;
    SignatureSender * m_pSender;
};

#endif // SIGNATURE_H
