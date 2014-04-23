#include "LoginInfo.h"

LoginInfo::LoginInfo()
{
}

void LoginInfo::insert(QString clinicName, QString index)
{
    if(clinicName.isEmpty())
        return;

    if(index.isEmpty())
        index = clinicName.at(0);

    m_mClinic[index] = clinicName;
}

bool LoginInfo::get(QString &index, QString & clinicName)
{
    std::map<QString,QString>::const_iterator it = m_mClinic.find(index);

    if(it == m_mClinic.end())
        return false;
    else
    {
        clinicName = it->second;
        return true;
    }
}

bool LoginInfo::isEmpty()
{
    return (m_mClinic.size() == 0) ;
}
