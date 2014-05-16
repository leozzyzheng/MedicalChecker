#ifndef CHECKPROXY_H
#define CHECKPROXY_H

#include "SqlEvent.h"
#include "Model/CheckInfo.h"

class CheckProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit CheckProxy(QObject *parent = 0);
    Q_INVOKABLE void queryTask(int weekDay);
    Q_INVOKABLE void queryRecord(QString date);
    Q_INVOKABLE int  getTaskNum();
    Q_INVOKABLE QString getData(int index);
    Q_INVOKABLE void sign(QString staffId, QString date, QString sig);

    void clear();
signals:
    void taskDataStandBy();
    void notChecked();
    void isChecked();
    void updateSucc();

protected slots:
    virtual void innerError(QSqlError &error);
    virtual void innerFinished(QSqlQueryEx query);

private:
    QString m_ClinicName;
    CheckInfo m_checkInfo;
    int m_currWeekDay;
};

#endif // CHECKPROXY_H
