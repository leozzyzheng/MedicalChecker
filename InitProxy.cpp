#include "InitProxy.h"

InitProxy::InitProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void InitProxy::excuteInit()
{
    QString sql = "SELECT clinicName FROM clinic.Clinic";
    m_pSqlOp->exec(sql);
}

void InitProxy::innerError(QSqlError &error)
{
    emit this->error("An error occured:" + error.text() + "!App is now exiting!");
}

void InitProxy::innerFinished(QSqlQuery &query)
{
    if(!query.isValid())
    {
        emit error("Cannot get clinic information!App is now exiting!");
        return;
    }

    while (query.next())
    {
        QString clinicName = query.value(0).toString();
        m_logInfo.insert(clinicName);
    }

    if(m_logInfo.isEmpty())
    {
        emit error("There is no clinic information!App is now exiting!");
        return;
    }

    emit completed();
}
