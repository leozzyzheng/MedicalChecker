#ifndef CHECKINFO_H
#define CHECKINFO_H

#include <vector>
#include <QString>

class CheckInfo
{
public:
    CheckInfo();
    void pushData(QString task);
    QString getDate(int index);
    int size();
    void clear();
private:
    std::vector<QString> m_vTask;
};

#endif // CHECKINFO_H
