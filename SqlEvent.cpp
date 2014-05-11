#include "SqlEvent.h"

SqlEvent::SqlEvent(QObject *parent) :
    QObject(parent)
{
    m_type = NONE;
    m_pSqlOp = SqlSingleton::getInstance();
}

void SqlEvent::exec(QSqlQueryEx & query)
{
    QSqlQueryEx * pQuery = new QSqlQueryEx(query);
    m_mPastQuery[pQuery] = 0;
    __innerconnect(pQuery);
    m_pSqlOp->exec(pQuery);
}

void SqlEvent::exec(QString &query)
{
    QSqlQueryEx * pQuery = new QSqlQueryEx(query);
    m_mPastQuery[pQuery] = 0;
    __innerconnect(pQuery);
    m_pSqlOp->exec(pQuery);
}

void SqlEvent::abort()
{
    m_mPastQuery.clear();
}

SqlEvent::EventType SqlEvent::type() const
{
    return m_type;
}

void SqlEvent::innerError(QSqlError & error)
{
    qDebug()<<"error";
    Q_UNUSED(error);
}

void SqlEvent::innerFinished(QSqlQueryEx query)
{
    Q_UNUSED(query);
}

void SqlEvent::__innerconnect(QSqlQueryEx* pQuery)
{
    connect((pQuery->getHelper()),SIGNAL(result(QSqlQueryEx*)),this,SLOT(__finished(QSqlQueryEx*)));
    connect((pQuery->getHelper()),SIGNAL(error(QSqlError&,QSqlQueryEx*)),this,SLOT(__error(QSqlError&,QSqlQueryEx*)));
}

void SqlEvent::__innerdisconnect(QSqlQueryEx* pQuery)
{
    disconnect((pQuery->getHelper()),SIGNAL(result(QSqlQueryEx*)),this,SLOT(__finished(QSqlQueryEx*)));
    disconnect((pQuery->getHelper()),SIGNAL(error(QSqlError&,QSqlQueryEx*)),this,SLOT(__error(QSqlError&,QSqlQueryEx*)));
}

void SqlEvent::__finished(QSqlQueryEx * query)
{
    if(m_mPastQuery.find(query) != m_mPastQuery.end())
    {
        QSqlQueryEx copy(*query);
        innerFinished(copy);
        __innerdisconnect(query);
        m_mPastQuery.erase(query);
    }
}

void SqlEvent::__error(QSqlError & error,QSqlQueryEx * query)
{
    if(m_mPastQuery.find(query) != m_mPastQuery.end())
    {
        innerError(error);
        __innerdisconnect(query);
        m_mPastQuery.erase(query);
    }

}
