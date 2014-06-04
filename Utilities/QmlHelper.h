#ifndef QMLHELPER_H
#define QMLHELPER_H

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QTimeZone>
#include <QDebug>
#include <map>
#include <QGuiApplication>

class QmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit QmlHelper(QObject *parent = 0);

public slots:
    void reset();
    QString getCurrDateTime(QString format = "yyyy-MM-dd");
    QString getCurrWeekDay();
    QString getCurrMonthName();
    int     getCurrWeekDayNum();
    QString addDay(int num, QString format = "yyyy-MM-dd");

    static  QString getCurrAbsDateTime(QString format = "yyyy-MM-dd");
    int     getCurrWeekNum();


    void    setData(QString key, QString value);
    QString getData(QString key);
    void    clearData(QString key);
    void    clearAllData();

    void    quit();
signals:
    void    appQuit();

private:
    QDateTime m_date;
    std::map<QString,QString> m_data;
};

#endif // QMLHELPER_H
