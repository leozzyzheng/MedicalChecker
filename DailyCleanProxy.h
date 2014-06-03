#ifndef DAILYCLEANPROXY_H
#define DAILYCLEANPROXY_H

#include "SqlEvent.h"
#include "Model/CleanInfo.h"

class DailyCleanProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit DailyCleanProxy(QObject *parent = 0);
public slots:
     void queryDaily();
     void queryDailyRecord(QString Date);
     QString getData(int index, QString key);
     int getTaskNum();
     void sign(QString taskContent, QString cleanTime, QString staffId, QString sig);

    void clear();

protected slots:
    virtual void innerError(QSqlErrorEx &error);
    virtual void innerFinished(QSqlQueryEx query);

signals:
    void taskContentStandBy();
    void recordStandBy();
    void updateSucc();

private:
    CleanInfo m_cleanInfo;
    QString   m_ClinicName;
};

#endif // DAILYCLEANPROXY_H
