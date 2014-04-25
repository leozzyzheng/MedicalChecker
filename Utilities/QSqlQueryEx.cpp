#include "QSqlQueryEx.h"

QSqlQueryEx::QSqlQueryEx(QSqlResult *r):
    QSqlQuery(r)
{

}

QSqlQueryEx::QSqlQueryEx(const QString &query, QSqlDatabase db):
    QSqlQuery(query,db)
{

}

QSqlQueryEx::QSqlQueryEx(QSqlDatabase db):
    QSqlQuery(db)
{

}

QSqlQueryEx::QSqlQueryEx(const QSqlQuery &other):
    QSqlQuery(other)
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
