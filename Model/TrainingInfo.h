#ifndef TRAININGINFO_H
#define TRAININGINFO_H

#include <QString>
#include <vector>

#define TRAINING_TIME_TAG       "trainingTime"
#define TRAINING_ADDR_TAG       "trainingAddr"
#define TRAINING_TYPE_TAG       "trainingType"
#define TRAINING_CONTENT_TAG    "trainingContent"
#define TRAINING_STAFF_TAG      "trainingStaff"
#define TRAINING_SUBMIT_TAG     "trainingSubmitTime"
#define TRAINING_STAFFID_TAG    "staff_Id"
#define TRAINING_STAFFSIGN_TAG  "IsSign_In"
#define TRAINING_TRAINID_TAG    "training_Id"


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
    };

    TrainingInfo();

    void clear();
    void pushData(DataStruct & data);
    void update(int index, QString signature);
    void pushSignData(TrainingInfo::StaffSignInfo & signData);

private:
    std::vector<DataStruct> m_vTrainingInfo;
    std::vector<StaffSignInfo> m_vSignInfo;
};

#endif // TRAININGINFO_H
