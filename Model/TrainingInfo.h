#ifndef TRAININGINFO_H
#define TRAININGINFO_H

#include <QString>
#include <vector>
#include <map>
#include <QDebug>
#include "Marco.h"

class TrainingInfo
{
public:
    typedef std::vector<std::map<QString,QString> > InfoVMap;

    TrainingInfo();

    void clear();
    void pushData(std::map<QString,QString> & data);
    void update(int index, QString signature);
    void pushSignData(std::map<QString,QString> & signData);
    int  trainingInfoSize();
    int  trainingStaffSize();
    QString getTrainingInfo(int index, QString & name);
    QString getSignInfo(int index, QString & name);
    void print();
private:

    InfoVMap m_vTrainingInfo;
    InfoVMap m_vSignInfo;
};

#endif // TRAININGINFO_H
