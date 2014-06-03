#include "QSqlErrorEx.h"

QSqlErrorEx::QSqlErrorEx(QString error)
{
    m_txt = error;
}

QSqlErrorEx::QSqlErrorEx(const QSqlErrorEx &other)
{
    m_txt = other.text();
}

QString QSqlErrorEx::text() const
{
    return m_txt;
}

void QSqlErrorEx::setText(const QString & text)
{
    m_txt = text;
}
