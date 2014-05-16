#include "CheckInfo.h"

CheckInfo::CheckInfo()
{
}

void CheckInfo::pushData(QString task, int id)
{
    m_vTask.push_back(task);
    m_mContentToId[task] = id;
}

QString CheckInfo::getDate(int index)
{
    if(m_vTask.size() <= index)
        return QString();
    else
        return m_vTask[index];
}

int CheckInfo::size()
{
    return m_vTask.size();
}

void CheckInfo::clear()
{
    m_vTask.clear();
    m_mContentToId.clear();
}

int CheckInfo::getId(QString content)
{
    std::map<QString,int>::iterator it = m_mContentToId.find(content);

    if(it == m_mContentToId.end())
        return -1;
    else
        return it->second;
}
