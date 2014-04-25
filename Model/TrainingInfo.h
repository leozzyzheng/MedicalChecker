#ifndef TRAININGINFO_H
#define TRAININGINFO_H

#include <QString>
#include <vector>

class TrainingInfo
{
public:
    struct StaffSignInfo
    {
        QString staffId;
        QString signature;
    };

    struct DataStruct
    {
        QString time;
        QString addr;
        QString type;
        QString content;
        QString staff;
        QString submitTime;
        QString id;
        std::vector<StaffSignInfo> signInfo;

        void _clear();
    };

    TrainingInfo();

    void clear();
    void setData(DataStruct data);
    const std::vector<TrainingInfo::StaffSignInfo> & getStaffSignInfo() const ;


private:
    DataStruct m_vTrainingInfo;
};

#endif // TRAININGINFO_H
