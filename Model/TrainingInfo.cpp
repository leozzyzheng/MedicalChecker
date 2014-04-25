#include "TrainingInfo.h"

TrainingInfo::TrainingInfo()
{
}

void TrainingInfo::clear()
{
    m_vTrainingInfo.clear();
}

void TrainingInfo::pushData(DataStruct & data)
{
    m_vTrainingInfo.push_back(data);
}

void TrainingInfo::update(int index, QString signature)
{
    if(m_vSignInfo.size() <= index)
        return;

    m_vSignInfo[index].signature = signature;
}

void TrainingInfo::pushSignData(TrainingInfo::StaffSignInfo & signData)
{
    m_vSignInfo.push_back(signData);
}
