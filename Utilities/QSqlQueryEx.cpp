#include "QSqlQueryEx.h"

QSqlQueryEx::QSqlQueryEx(QSqlResult *r):
    QSqlQuery(r)
{

}

QSqlQueryEx::QSqlQueryEx(const QString &query, QSqlDatabase db):
    QSqlQuery("",db)
{
    if(!query.isEmpty())
        prepare(query);
}

QSqlQueryEx::QSqlQueryEx(QSqlDatabase db):
    QSqlQuery(db)
{

}

QSqlQueryEx::QSqlQueryEx(const QSqlQueryEx &other):
    QSqlQuery(other)
{
    m_id = other.getID();
}

void QSqlQueryEx::setID(const QString &id)
{
    m_id = id;
}

const QString &QSqlQueryEx::getID() const
{
    return m_id;
}

QueryHelper * QSqlQueryEx::getHelper()
{
    return &m_helper;
}

void QSqlQueryEx::emitResult()
{
    m_helper.emitResult(this);
}

void QSqlQueryEx::emitError(QSqlError & error)
{
    m_helper.emitError(error, this);
}


