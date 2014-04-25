#include "InitProxy.h"

InitProxy::InitProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void InitProxy::excuteInit()
{
    QString sql = "SELECT clinicName FROM QMLTEST.clinic";
    m_pSqlOp->exec(sql);
}

int InitProxy::getInfoNum()
{
    return m_vIndicator.size();
}

void InitProxy::excuteIndicator(QString key)
{
    m_vIndicator.clear();
    m_logInfo.get(key,m_vIndicator);
}

QString InitProxy::getShownName(int index)
{
    if(m_vIndicator.size() <= index)
        return QString();

    return m_vIndicator[index].shownName;
}

QString InitProxy::getOriginName(int index)
{
    if(m_vIndicator.size() <= index)
        return QString();

    return m_vIndicator[index].originName;
}

void InitProxy::innerError(QSqlError &error)
{
    emit this->error("An error occured:" + error.text() + "!App is now exiting!");
}

void InitProxy::innerFinished(QSqlQueryEx &query)
{
    if(!query.isActive())
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

    m_logInfo.sort();

    emit completed();
}
