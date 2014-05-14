#include "LoginInfo.h"
#include <qDebug>

LoginInfo::LoginInfo()
{
}

void LoginInfo::insert(QString clinicName)
{
    if(clinicName.isEmpty())
        return;

    m_clinic.append(clinicName);
}

void LoginInfo::get(QString &key, std::vector<dataStruct> & clinicNames)
{
    for(int i = 0; i < m_clinic.length(); ++i)
    {
        QString temp = m_clinic.at(i);
        int index = temp.indexOf(key, 0, Qt::CaseInsensitive);

        if(index == -1)
            continue;

        if(key.compare(temp,Qt::CaseInsensitive) == 0)
            continue;

        QString origin = temp;
        temp.insert(index + key.length(), "</b>");
        temp.insert(index,"<b>");

        dataStruct tempStruct;
        tempStruct.shownName = temp;
        tempStruct.originName = origin;
        clinicNames.push_back(tempStruct);
    }
}

void LoginInfo::sort()
{
    m_clinic.sort();
}

bool LoginInfo::isEmpty()
{
    return (m_clinic.size() == 0) ;
}

