#include "CleanInfo.h"

CleanInfo::CleanInfo()
{
}

void CleanInfo::setContentTableData(int index, const QString &content)
{
    //qDebug()<<index<<content;
    m_mContentTable[index] = content;
    m_mContentToId[content] = index;
}

void CleanInfo::setStaffTableData(int index, const QString &staff)
{
    m_mStaffTable[index] = staff;
}

QString CleanInfo::getContentData(int index)
{
    std::map<int, QString>::iterator it = m_mContentTable.find(index);

    if(it != m_mContentTable.end())
        return it->second;
    else
        return QString();
}

QString CleanInfo::getStaffData(int index)
{
    std::map<int, QString>::iterator it = m_mStaffTable.find(index);

    if(it != m_mStaffTable.end())
        return it->second;
    else
        return QString();
}

void CleanInfo::setData(int index, std::map<QString,QString> & datamap)
{
    m_data[index] = datamap;
}

void CleanInfo::setData(int index, const QString &key, const QString &value)
{
    m_data[index][key] = value;
}

QString CleanInfo::getData(int index, QString & key)
{
    index = getId(index);

    DataMap::const_iterator iter = m_data.find(index);

    if(iter == m_data.end())
        return QString();

    std::map<QString,QString>::iterator it = m_data[index].find(key);

    if(it != m_data[index].end())
    {
        //qDebug()<<it->second;
        return it->second;
    }
    else
        return QString();
}

void CleanInfo::pushId(int index)
{
    m_vId.push_back(index);
}

int CleanInfo::getId(int index)
{
    if(m_vId.size() <= index)
        return -1;
    else
        return m_vId[index];
}

int CleanInfo::getContentTableSize()
{
    return m_mContentTable.size();
}

int CleanInfo::getDataSize()
{
    return m_data.size();
}

int CleanInfo::getStaffTableSize()
{
    return m_mStaffTable.size();
}

void CleanInfo::clear()
{
    m_mContentTable.clear();
    m_data.clear();
    m_mStaffTable.clear();
    m_vId.clear();
    m_mContentToId.clear();
}

void CleanInfo::print()
{
    qDebug()<<"TaskContent";
    std::map<int,QString>::iterator it = m_mContentTable.begin();

    for(;it != m_mContentTable.end(); ++it)
    {
        qDebug()<<"index:"<<it->first<<" value:"<<it->second;
    }

    qDebug()<<"Staff";
    it = m_mStaffTable.begin();

    for(;it != m_mStaffTable.end(); ++it)
    {
        qDebug()<<"index:"<<it->first<<" value:"<<it->second;
    }

    CleanInfo::DataMap::iterator iter = m_data.begin();

    for(;iter != m_data.end(); ++iter)
    {
        qDebug()<<iter->first;
        std::map<QString,QString>::iterator innerIt = iter->second.begin();

        for(; innerIt != iter->second.end(); ++innerIt)
        {
            qDebug()<<"name:"<<innerIt->first<<" value:"<<innerIt->second;
        }
    }
}

int CleanInfo::getIdFromContent(QString content)
{
    std::map<QString,int>::iterator it = m_mContentToId.find(content);

    if(it != m_mContentToId.end())
        return it->second;
    else
        return -1;
}
