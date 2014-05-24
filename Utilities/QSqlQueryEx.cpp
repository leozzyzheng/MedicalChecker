#include "QSqlQueryEx.h"

QSqlQueryEx::QSqlQueryEx(QSqlResult *r):
    QSqlQuery(r),
    m_bCanExecute(true)
{

}

QSqlQueryEx::QSqlQueryEx(const QString &query, QSqlDatabase db):
    QSqlQuery("",db),
    m_bCanExecute(true)
{
    m_sql = query;
}

QSqlQueryEx::QSqlQueryEx(QSqlDatabase db):
    QSqlQuery(db),
    m_bCanExecute(true)
{

}

QSqlQueryEx::QSqlQueryEx(const QSqlQueryEx &other):
    QSqlQuery(other)
{
    m_id = other.getID();
    m_sql = other.getSqlString();
    m_bCanExecute = other.getExecutable();
}

void QSqlQueryEx::setID(const QString &id)
{
    m_id = id;
}

const QString &QSqlQueryEx::getID() const
{
    return m_id;
}

QString QSqlQueryEx::getSqlString() const
{
    return m_sql;
}

void QSqlQueryEx::setSqlString(const QString &sql)
{
    m_vPre.clear();
    m_sql = sql;
}

void QSqlQueryEx::replaceHolder(const QString &holder, const QVariant &value)
{
    QString v = value.toString();
    m_sql.replace(holder,v);
}

void QSqlQueryEx::threaBindValue(const QString &holder, const QVariant &value)
{
    PrepareData data;
    data.holder = holder;
    data.value = value;
    m_vPre.push_back(data);
}

void QSqlQueryEx::setExecutable(bool excutable)
{
    m_bCanExecute = excutable;
}

bool QSqlQueryEx::getExecutable() const
{
    return m_bCanExecute;
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

void QSqlQueryEx::bindAll()
{
    std::vector<PrepareData>::iterator it = m_vPre.begin();

    for(;it != m_vPre.end();++it)
    {
        PrepareData data = *it;
        this->bindValue(data.holder,data.value);
    }
}


