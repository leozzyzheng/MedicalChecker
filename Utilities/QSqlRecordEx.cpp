#include "QSqlRecordEx.h"

QSqlRecordEx::QSqlRecordEx()
{
}

QSqlRecordEx::QSqlRecordEx(const QSqlRecordEx &other)
{
    int num = other.size();

    for(int i = 0; i < num; ++i)
    {
        QVariantMap map;

        map.insert(other.key(i),other.value(i));

        push(map);
    }
}

void QSqlRecordEx::push(const QVariantMap &map)
{
    if(map.size() == 0)
        return;

    m_data.clear();
    m_keys.clear();

    QVariantMap::const_iterator it = map.constBegin();

    for(; it != map.constEnd(); ++it)
    {
        m_data.push_back(it.value());
        m_keys.push_back(it.key());
    }
}

int QSqlRecordEx::indexOf(const QString &key)
{
    for(int i = 0; i < m_keys.size(); ++i)
    {
        if(m_keys.at(i) == key)
            return i;
    }

    return -1;
}

QVariant QSqlRecordEx::value(int index) const
{
    if(index >=  m_data.size())
        return QVariant();
    else
        return m_data[index];
}

QString QSqlRecordEx::key(int index) const
{
    if(index >= m_keys.size())
    {
        return QString();
    }
    else
    {
        return m_keys[index];
    }
}

int QSqlRecordEx::size() const
{
    return m_data.size();
}


