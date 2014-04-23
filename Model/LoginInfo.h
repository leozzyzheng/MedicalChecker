#ifndef LOGININFO_H
#define LOGININFO_H

//初始登录APP信息存储类

#include <map>
#include <QString>

class LoginInfo
{
public:
    LoginInfo();

    void insert(QString clinicName, QString index = QString());
    bool get(QString & index , QString & clinicName);
    bool isEmpty();

private:
    std::map<QString,QString> m_mClinic;
};

#endif // LOGININFO_H
