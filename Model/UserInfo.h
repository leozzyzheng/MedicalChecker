#ifndef USERINFO_H
#define USERINFO_H

#include <map>
#include <vector>
#include <QString>
#include "Marco.h"

class UserInfo
{
public:
    typedef std::map<QString, std::map<QString,QString> > DataMap;

    UserInfo();

    struct IdAndName
    {
        QString id;
        QString name;
    };

    void setData(QString idnumber, std::map<QString,QString> & data);
    void setData(QString idnumber, QString & key, QString & value);
    QString getData(QString idnumber, QString & key);
    int size();
    void clear();
    void prepareName(QString staffId);
    QString getUserId(int index);
    QString getUserName(int index);
    int nameSize();

private:
    DataMap m_data;
    std::vector<IdAndName> m_vTempName;
};

#endif // USERINFO_H
