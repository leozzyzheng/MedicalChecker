#include "GlobalHelper.h"

GlobalHelper::GlobalHelper(QObject *parent) :
    QObject(parent)
{
}

void GlobalHelper::getUserAndPw(QString &username, QString &passwd)
{
    QSettings settings("MedicalChecker", "MedicalChecker");
    username = settings.value("username").toString();
    passwd = settings.value("passwd").toString();
}

void GlobalHelper::setUserAndPw(const QString &username, const QString &passwd)
{
    QSettings settings("MedicalChecker", "MedicalChecker");
    settings.setValue("username",username);
    settings.setValue("passwd",passwd);
}

void GlobalHelper::setGlobalValue(const QString &name, const QString &value)
{
    QCoreApplication::instance()->setProperty(name.toUtf8().constData(),value);
}

QString GlobalHelper::getGlobalValue(const QString &name)
{
    QVariant value = QCoreApplication::instance()->property(name.toUtf8().constData());

    if(!value.isValid())
    {
        qDebug()<<"No Global value named: "<<name<<".Empty String will be returned";
        return QString();
    }
    else
    {
        return value.toString();
    }
}

void GlobalHelper::clearGloabalValue(const QString &name)
{
    QCoreApplication::instance()->setProperty(name.toUtf8().constData(),QVariant());
}
