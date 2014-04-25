#ifndef QMLHELPER_H
#define QMLHELPER_H

#include <QObject>
#include <QDateTime>
#include <QStringList>

class QmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit QmlHelper(QObject *parent = 0);

signals:

public slots:
    QString getCurrDateTime(QString format = "yyyy-MM-dd");
    QString getCurrWeekDay();
    QString addDay(QString date, int num);
};

#endif // QMLHELPER_H
