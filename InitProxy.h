#ifndef INITSQLEVENT_H
#define INITSQLEVENT_H

#include "SqlEvent.h"
#include "Model/LoginInfo.h"
#include "Utilities/GlobalHelper.h"

class InitProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit InitProxy(QObject *parent = 0);
public slots:
     bool excuteInit();
     int getInfoNum();
     void excuteIndicator(QString key);
     QString getShownName(int index);
     QString getOriginName(int index);
     void login(QString username, QString passwd);
signals:
    void loginFail();
    void loginSucc();
    void notOpened();
public slots:
protected slots:
    void innerError(QSqlError & error);
    void innerFinished(QSqlQueryEx query);
private:
    LoginInfo m_logInfo;
    std::vector<LoginInfo::dataStruct> m_vIndicator;
};

#endif // INITSQLEVENT_H
