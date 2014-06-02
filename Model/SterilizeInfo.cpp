#include "SterilizeInfo.h"

SterilizeInfo::SterilizeInfo()
{
}

void SterilizeInfo::clear()
{
    m_data.clear();
}

void SterilizeInfo::setData(std::map<QString, QString> &data)
{
    m_data.push_back(data);
}

QString SterilizeInfo::getData(int index, const QString &key)
{
    if(index >= m_data.size())
        return QString();
    else
    {
        std::map<QString,QString>::iterator it = m_data[index].find(key);
        if(it != m_data[index].end())
            return m_data[index][key];
        else
            return QString();
    }
}

int SterilizeInfo::getNum()
{
    return m_data.size();
}
