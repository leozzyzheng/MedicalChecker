#include "UserInfo.h"

UserInfo::UserInfo()
{
}

void UserInfo::setData(QString idnumber, std::map<QString, QString> &data)
{
    m_data[idnumber] = data;
}

void UserInfo::setData(QString idnumber, QString &key, QString &value)
{
    m_data[idnumber][key] = value;
}

QString UserInfo::getData(QString idnumber, QString &key)
{
    DataMap::iterator it = m_data.find(idnumber);

    if(it == m_data.end())
        return QString();

    std::map<QString, QString>::iterator iter = it->second.find(key);

    if(iter == it->second.end())
        return QString();

    return iter->second;
}

int UserInfo::size()
{
    return m_data.size();
}

void UserInfo::clear()
{
    m_data.clear();
}

void UserInfo::prepareName(QString staffId)
{
    m_vTempName.clear();

    if(!staffId.isEmpty() && staffId != "null" && !staffId.isNull())
    {
        DataMap::iterator it = m_data.find(staffId);

        if(it != m_data.end())
        {
            std::map<QString,QString>::iterator iter = it->second.find(USER_NAME_TAG);

            if(iter != it->second.end())
            {
                IdAndName info;
                info.id = it->first;
                info.name = iter->second;
                m_vTempName.push_back(info);
            }
        }

        return;
    }

    DataMap::iterator it = m_data.begin();

    for(; it != m_data.end(); ++it)
    {
        std::map<QString,QString>::iterator iter = it->second.find(USER_NAME_TAG);

        if(iter != it->second.end())
        {
            IdAndName info;
            info.id = it->first;
            info.name = iter->second;
            m_vTempName.push_back(info);
        }
    }
}

QString UserInfo::getUserId(int index)
{
    if(m_vTempName.size() <= index)
        return QString();

    return m_vTempName[index].id;
}

QString UserInfo::getUserName(int index)
{
    if(m_vTempName.size() <= index)
        return QString();

    return m_vTempName[index].name;
}

int UserInfo::nameSize()
{
    return m_vTempName.size();
}


