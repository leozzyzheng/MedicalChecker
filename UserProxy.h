#ifndef USERPROXY_H
#define USERPROXY_H

#include "SqlEvent.h"
#include "Model/UserInfo.h"

class UserProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit UserProxy(QObject * parent = 0);
public slots:
     void queryUser();
     QString getData(QString idnumber, QString key);
     void prepareName(QString staffId);
     QString getUserName(int index);
     QString getUserId(int index);
     int nameSize();

    void clear();

protected slots:
    void innerError(QSqlError & error);
    void innerFinished(QSqlQueryEx query);
signals:
    void userDataStandBy();
private:
    QString m_ClinicName;
    UserInfo m_userInfo;
};

#endif // USERPROXY_H
