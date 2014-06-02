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
    void setData(std::map<QString,QString> & data);
    QString getData(int index, const QString &key);
    int getNum();

private:
    DataMap m_data;
};

#endif // SterilizeINFO_H
