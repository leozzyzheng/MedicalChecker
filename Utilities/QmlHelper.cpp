#include "QmlHelper.h"

QmlHelper::QmlHelper(QObject *parent) :
    QObject(parent)
{
}

QString QmlHelper::getCurrDateTime(QString format)
{
    return QDateTime::currentDateTime().toString(format);
}

QString QmlHelper::getCurrWeekDay()
{
    int weekDay = QDate::currentDate().dayOfWeek();
    return QDate::longDayName(weekDay);
}

QString QmlHelper::addDay(QString date, int num)
{
    QStringList list = date.split("-");

    if(list.length() != 3)
        return QString();

    int y = list.at(0).toInt();
    int m = list.at(1).toInt();
    int d = list.at(2).toInt();

    QDate tempDate(y, m, d);

    if(!tempDate.isValid())
        return QString();

    tempDate = tempDate.addDays(num);
    return tempDate.toString("yyyy-MM-dd");
}
