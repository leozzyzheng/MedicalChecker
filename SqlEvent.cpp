#include "SqlEvent.h"

SqlEvent::SqlEvent(QObject *parent) :
    QObject(parent)
{
    m_type = NONE;
    m_pSqlOp = SqlSingleton::getInstance();
    connect(m_pSqlOp, SIGNAL(result(QSqlQuery&)), this, SIGNAL(result(QSqlQuery&)));
    connect(m_pSqlOp, SIGNAL(error(QSqlError&)),  this, SIGNAL(error(QSqlError&)));
    connect(m_pSqlOp, SIGNAL(error(QSqlError&)), this, SLOT(innerError(QSqlError&)));
    connect(m_pSqlOp, SIGNAL(result(QSqlQuery&)), this, SLOT(innerFinished(QSqlQuery&)));
}

SqlEvent::EventType SqlEvent::type() const
{
    return m_type;
}

void SqlEvent::innerError(QSqlError &error)
{

}

void SqlEvent::innerFinished(QSqlQuery &query)
{

}
