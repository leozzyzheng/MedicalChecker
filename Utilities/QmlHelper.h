#ifndef QMLHELPER_H
#define QMLHELPER_H

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QTimeZone>
#include <QDebug>

class QmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit QmlHelper(QObject *parent = 0);

signals:

public slots:
    void reset();
    QString getCurrDateTime(QString format = "yyyy-MM-dd");
    QString getCurrWeekDay();
    QString getCurrMonthName();
    QString addDay(int num, QString format = "yyyy-MM-dd");
private:
    QDateTime m_date;
};

#endif // QMLHELPER_H
