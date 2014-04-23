#ifndef INITSQLEVENT_H
#define INITSQLEVENT_H

#include "SqlEvent.h"
#include "Model/LoginInfo.h"

class InitProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit InitProxy(QObject *parent = 0);
    Q_INVOKABLE void excuteInit();
    Q_INVOKABLE int getInfoNum();
    Q_INVOKABLE void excuteIndicator(QString key);
    Q_INVOKABLE QString getShownName(int index);
    Q_INVOKABLE QString getOriginName(int index);
signals:
    void completed();
    void error(QString errorString);
public slots:
protected slots:
    void innerError(QSqlError& error);
    void innerFinished(QSqlQuery & query);
private:
    LoginInfo m_logInfo;
    std::vector<LoginInfo::dataStruct> m_vIndicator;
};

#endif // INITSQLEVENT_H