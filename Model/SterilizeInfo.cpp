#include "SterilizeInfo.h"

SterilizeInfo::SterilizeInfo()
{
}

void SterilizeInfo::clear()
{
    m_data.clear();
}

void SterilizeInfo::setData(std::map<QString, QString> &data, QString id)
{
    m_data.push_back(data);
    m_IdToIndex[id] = m_data.size() - 1;
}

void SterilizeInfo::setRecordData(std::map<QString, QString> &data, QString id)
{
    std::map<QString,int>::iterator it = m_IdToIndex.find(id);

    if(it != m_IdToIndex.end())
    {
        int index = it->second;

        if(index >= m_data.size())
            return;

        std::map<QString,QString>::iterator iter = data.begin();

        for(;iter != data.end(); ++iter)
        {
            m_data[index][iter->first] = iter->second;
        }
    }
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
