#include "SqlEvent.h"

SqlEvent::SqlEvent(QObject *parent) :
    QObject(parent)
{
    m_type = NONE;
    m_pSqlOp = SqlSingleton::getInstance();
    connect(m_pSqlOp, SIGNAL(result(QSqlQuery&)), this, SIGNAL(result(QSqlQuery&)));
    connect(m_pSqlOp, SIGNAL(error(QSqlError&)),  this, SIGNAL(error(QSqlError&)));
}

SqlEvent::EventType SqlEvent::type() const
{
    return m_type;
}
