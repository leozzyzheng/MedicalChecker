#ifndef LOGININFO_H
#define LOGININFO_H

//初始登录APP信息存储类

#include <vector>
#include <QString>
#include <QStringList>

class LoginInfo
{
public:
    struct dataStruct
    {
        QString shownName;
        QString originName;
    };

    LoginInfo();

    void insert(QString clinicName);
    void get(QString & key , std::vector<dataStruct> & clinicNames);
    void sort();
    bool isEmpty();

private:
    QStringList m_clinic;
};

#endif // LOGININFO_H
