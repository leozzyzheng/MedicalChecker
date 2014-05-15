#include "CheckInfo.h"

CheckInfo::CheckInfo()
{
}

void CheckInfo::pushData(QString task)
{
    m_vTask.push_back(task);
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
}
