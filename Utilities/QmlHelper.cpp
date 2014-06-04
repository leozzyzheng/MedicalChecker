#include "QmlHelper.h"

QmlHelper::QmlHelper(QObject *parent) :
    QObject(parent)
{
    reset();
    connect(this,SIGNAL(appQuit()),QGuiApplication::instance(),SLOT(quit()));
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

int QmlHelper::getCurrWeekDayNum()
{
    return m_date.date().dayOfWeek();
}

QString QmlHelper::addDay(int num, QString format)
{
    m_date = m_date.addDays(num);
    return QLocale().toString(m_date, format);
}

QString QmlHelper::getCurrAbsDateTime(QString format)
{
    QDateTime temp = QDateTime::currentDateTime();
    temp.setTimeZone(QTimeZone(QTimeZone::systemTimeZoneId()));
    return QLocale().toString(temp, format);
}

int QmlHelper::getCurrWeekNum()
{
    return 1;
}

void QmlHelper::setData(QString key, QString value)
{
    m_data[key] = value;
}

QString QmlHelper::getData(QString key)
{
    std::map<QString,QString>::iterator it = m_data.find(key);

    if(it != m_data.end())
    {
        return it->second;
    }
    else
    {
        return QString();
    }
}

void QmlHelper::clearData(QString key)
{
    std::map<QString,QString>::iterator it = m_data.find(key);

    if(it != m_data.end())
        m_data.erase(it);
}

void QmlHelper::clearAllData()
{
    m_data.clear();
}

void QmlHelper::quit()
{
    emit appQuit();
}
