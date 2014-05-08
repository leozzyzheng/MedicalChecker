#include "QmlHelper.h"

QmlHelper::QmlHelper(QObject *parent) :
    QObject(parent)
{
    reset();
}

void QmlHelper::reset()
{
    m_date = QDateTime::currentDateTime();
    m_date.setTimeZone(QTimeZone(QTimeZone::systemTimeZoneId()));
}

QString QmlHelper::getCurrDateTime(QString format)
{
    return QLocale().toString(m_date, format);
}

QString QmlHelper::getCurrWeekDay()
{
    return QLocale().dayName(m_date.date().dayOfWeek(),QLocale::ShortFormat);
}

QString QmlHelper::getCurrMonthName()
{
    return QLocale().monthName(m_date.date().month(),QLocale::ShortFormat);
}

QString QmlHelper::addDay(int num, QString format)
{
    m_date = m_date.addDays(num);
    return QLocale().toString(m_date, format);
}
