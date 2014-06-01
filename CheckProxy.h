#ifndef CHECKPROXY_H
#define CHECKPROXY_H

#include "SqlEvent.h"
#include "Model/CheckInfo.h"

class CheckProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit CheckProxy(QObject *parent = 0);
public slots:
     void queryTask(int weekDay);
     void queryRecord(QString date);
     int  getTaskNum();
     QString getData(int index);
     void sign(QString staffId, QString date, QString sig);

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
