#ifndef WEEKLYCLEANPROXY_H
#define WEEKLYCLEANPROXY_H

#include "SqlEvent.h"
#include "Model/CleanInfo.h"

class WeeklyCleanProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit WeeklyCleanProxy(QObject *parent = 0);
    Q_INVOKABLE void queryWeekly();
    Q_INVOKABLE void queryRecord(QString weekNum);
    Q_INVOKABLE int getTaskNum();
    Q_INVOKABLE QString getData(int index, QString key);
    Q_INVOKABLE void sign(QString taskContent, int week, QString staffId, QString sig);

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
