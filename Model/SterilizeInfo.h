#ifndef SterilizeINFO_H
#define SterilizeINFO_H

#include <map>
#include <vector>
#include <QString>

class SterilizeInfo
{
public:
    typedef std::vector<std::map< QString,QString> > DataMap;
    SterilizeInfo();

    void clear();
    void setData(std::map<QString,QString> & data, QString id);
    void setRecordData(std::map<QString,QString> & data, QString id);
    QString getData(int index, const QString &key);
    int getNum();

private:
    DataMap m_data;
    std::map<QString,int> m_IdToIndex;
};

#endif // SterilizeINFO_H
