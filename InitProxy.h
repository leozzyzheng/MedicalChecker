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
signals:
    void completed();
    void error(QString errorString);
public slots:
protected slots:
    void innerError(QSqlError& error);
    void innerFinished(QSqlQuery & query);
private:
    LoginInfo m_logInfo;
};

#endif // INITSQLEVENT_H
