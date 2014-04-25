#include "SqlEvent.h"

SqlEvent::SqlEvent(QObject *parent) :
    QObject(parent)
{
    m_type = NONE;
    m_pSqlOp = SqlSingleton::getInstance();
    connect(m_pSqlOp, SIGNAL(result(QSqlQueryEx&)), this, SIGNAL(originResult(QSqlQueryEx&)));
    connect(m_pSqlOp, SIGNAL(error(QSqlError&)),  this, SIGNAL(priginError(QSqlError&)));
    connect(m_pSqlOp, SIGNAL(error(QSqlError&)), this, SLOT(innerError(QSqlError&)));
    connect(m_pSqlOp, SIGNAL(result(QSqlQueryEx&)), this, SLOT(innerFinished(QSqlQueryEx&)));
}

SqlEvent::EventType SqlEvent::type() const
{
    return m_type;
}

void SqlEvent::innerError(QSqlError &error)
{

}

void SqlEvent::innerFinished(QSqlQueryEx &query)
{

}
