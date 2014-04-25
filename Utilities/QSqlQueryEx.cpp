#include "QSqlQueryEx.h"

QSqlQueryEx::QSqlQueryEx()
{
}

void QSqlQueryEx::setID(QString & id)
{
    m_id = id;
}

const QString &QSqlQueryEx::getID() const
{
    return m_id;
}

void QSqlQueryEx::setID(QString id)
{
    m_id = id;
}
