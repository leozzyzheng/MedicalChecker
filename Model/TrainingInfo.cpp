#include "TrainingInfo.h"

TrainingInfo::TrainingInfo()
{
}

void TrainingInfo::clear()
{
    m_vTrainingInfo._clear();
}

void TrainingInfo::setData(TrainingInfo::DataStruct data)
{
    m_vTrainingInfo.time = data.time;
    m_vTrainingInfo.addr = data.addr;
    m_vTrainingInfo.type = data.type;
    m_vTrainingInfo.content = data.content;
    m_vTrainingInfo.staff = data.staff;
    m_vTrainingInfo.submitTime = data.submitTime;
    m_vTrainingInfo.id = data.id;
    m_vTrainingInfo.signInfo = data.signInfo;
}

const std::vector<TrainingInfo::StaffSignInfo> &TrainingInfo::getStaffSignInfo() const
{
    return m_vTrainingInfo.signInfo;
}

void TrainingInfo::update(int index, QString signature)
{
    if(m_vTrainingInfo.signInfo.size() <= index)
        return;

    m_vTrainingInfo.signInfo[index].signature = signature;
}


void TrainingInfo::DataStruct::_clear()
{
    time.clear();
    addr.clear();
    type.clear();
    content.clear();
    staff.clear();
    submitTime.clear();
    id.clear();
    signInfo.clear();
}
