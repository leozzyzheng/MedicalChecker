#ifndef USERPROXY_H
#define USERPROXY_H

#include "SqlEvent.h"
#include "Model/UserInfo.h"

class UserProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit UserProxy(QObject * parent = 0);
    Q_INVOKABLE void queryUser();
    Q_INVOKABLE QString getData(QString idnumber, QString key);
    Q_INVOKABLE void prepareName(QString staffId);
    Q_INVOKABLE QString getUserName(int index);
    Q_INVOKABLE QString getUserId(int index);
    Q_INVOKABLE int nameSize();

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
