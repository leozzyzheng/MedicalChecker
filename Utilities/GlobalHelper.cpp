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

void GlobalHelper::setUserAndPw(QString &username, QString &passwd)
{
    QSettings settings("MedicalChecker", "MedicalChecker");
    settings.setValue("username",username);
    settings.setValue("passwd",passwd);
}

void GlobalHelper::setGlobalValue(QString &name, QString &value)
{
    QCoreApplication::instance()->setProperty(name.toUtf8().constData(),value);
}

QString GlobalHelper::getGlobalValue(QString &name)
{
    return QCoreApplication::instance()->property(name.toUtf8().constData()).toString();
}
