#include "InitProxy.h"

InitProxy::InitProxy(QObject *parent) :
    SqlEvent(parent)
{
}

bool InitProxy::excuteInit()
{
    QSqlQueryEx test("test");

    if(!test.driver()->isOpen())
    {
        emit notOpened();
        return false;
    }

    QString sql = "SELECT clinicName FROM `TheWholeClinicName`.ClinicName";
    exec(sql);
    return true;
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

void InitProxy::login(QString username, QString passwd)
{
    QSqlQueryEx sql;
    sql.setSqlString(QString("select * from") + "`" + username + "`.Clinic where cmPassword = :passwd");
    sql.replaceHolder(":passwd",passwd);
    sql.setID("login");
    GlobalHelper::setGlobalValue("ClinicName",username);
    exec(sql);
}

void InitProxy::innerError(QSqlError & error)
{
    emit this->error("An error occured:" + error.text() + "!");
}

void InitProxy::innerFinished(QSqlQueryEx query)
{
    if(query.getID() == "login")
    {
        if(query.size() != 1)
        {
            GlobalHelper::clearGloabalValue("ClinicName");
            emit loginFail();
        }
        else
        {
            emit loginSucc();
        }

        return;
    }


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
