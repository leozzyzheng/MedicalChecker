#ifndef CHECKINFO_H
#define CHECKINFO_H

#include <vector>
#include <QString>
#include <map>

class CheckInfo
{
public:
    CheckInfo();
    void pushData(QString task,int id);
    QString getDate(int index);
    int size();
    void clear();
    int getId(QString content);
private:
    std::vector<QString> m_vTask;
    std::map<QString,int> m_mContentToId;
};

#endif // CHECKINFO_H
