#include "CleanInfo.h"

CleanInfo::CleanInfo()
{
}

void CleanInfo::setContentTableData(int index, const QString &content)
{
    m_mContentTable[index] = content;
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

QString CleanInfo::getData(int index, QString & key)
{
    if(m_data.size() <= index)
        return QString();

    std::map<QString,QString>::iterator it = m_data[index].find(key);

    if(it != m_data[index].end())
        return it->second;
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
}
