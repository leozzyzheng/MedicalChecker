#include "TrainingInfo.h"

TrainingInfo::TrainingInfo()
{
}

void TrainingInfo::clear()
{
    m_vTrainingInfo.clear();
    m_vSignInfo.clear();
}

void TrainingInfo::clearSignInfo()
{
    m_vSignInfo.clear();
}

void TrainingInfo::pushData(std::map<QString,QString> & data)
{
    m_vTrainingInfo.push_back(data);
}

void TrainingInfo::update(int index, QString signature)
{
    if(m_vSignInfo.size() <= index)
        return;

    m_vSignInfo[index][TRAINING_STAFFSIGN_TAG] = signature;
}

void TrainingInfo::pushSignData(std::map<QString, QString> &signData)
{
    m_vSignInfo.push_back(signData);
}

int TrainingInfo::trainingStaffSize()
{
    return m_vSignInfo.size();
}

QString TrainingInfo::getTrainingInfo(int index, QString & name)
{
    if(m_vTrainingInfo.size() <=  index)
        return QString();

    std::map<QString,QString>::iterator it = m_vTrainingInfo[index].find(name);

    if(it == m_vTrainingInfo[index].end())
        return QString();
    else
        return it->second;
}

QString TrainingInfo::getSignInfo(int index, QString & name)
{
    if(m_vSignInfo.size() <=  index)
        return QString();

    std::map<QString,QString>::iterator it = m_vSignInfo[index].find(name);

    if(it == m_vSignInfo[index].end())
        return QString();
    else
    {
        qDebug()<<it->second;
        return it->second;
    }
}

void TrainingInfo::print()
{
    for(int i = 0; i < m_vTrainingInfo.size(); ++i)
    {
        qDebug()<<"index:"<<i;

        std::map<QString,QString>::iterator it = m_vTrainingInfo[i].begin();

        for(; it != m_vTrainingInfo[i].end(); ++it)
        {
            qDebug()<<"name:"<<it->first<<" value:"<<it->second;
        }
    }

    for(int i = 0; i < m_vSignInfo.size(); ++i)
    {
        qDebug()<<"index:"<<i;

        std::map<QString,QString>::iterator it = m_vSignInfo[i].begin();

        for(; it != m_vSignInfo[i].end(); ++it)
        {
            qDebug()<<"name:"<<it->first<<" value:"<<it->second;
        }
    }

}

int TrainingInfo::trainingInfoSize()
{
    return m_vTrainingInfo.size();
}
