#ifndef WEEKLYCLEANPROXY_H
#define WEEKLYCLEANPROXY_H

#include "SqlEvent.h"
#include "Model/CleanInfo.h"

class WeeklyCleanProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit WeeklyCleanProxy(QObject *parent = 0);
public slots:
     void queryWeekly();
     void queryRecord(QString weekNum);
     int getTaskNum();
     QString getData(int index, QString key);
     void sign(QString taskContent, int week, QString staffId, QString sig);

    void clear();
signals:
    void taskDataStandBy();
    void recordDataStandBy();
    void updateSucc();

protected slots:
    virtual void innerError(QSqlError &error);
    virtual void innerFinished(QSqlQueryEx query);

private:
    CleanInfo m_cleanInfo;
    QString m_ClinicName;
};

#endif // WEEKLYCLEANPROXY_H
