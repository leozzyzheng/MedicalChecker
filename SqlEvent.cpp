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
    __innerconnect(pQuery);
    m_pSqlOp->exec(pQuery);
}

void SqlEvent::exec(QString &query)
{
    QSqlQueryEx * pQuery = new QSqlQueryEx(query);
    __innerconnect(pQuery);
    m_pSqlOp->exec(pQuery);
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
    QSqlQueryEx copy(*query);
    innerFinished(copy);
    __innerdisconnect(query);
}

void SqlEvent::__error(QSqlError & error,QSqlQueryEx * query)
{
    innerError(error);
    __innerdisconnect(query);
}
