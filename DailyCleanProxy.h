#ifndef DAILYCLEANPROXY_H
#define DAILYCLEANPROXY_H

#include "SqlEvent.h"
#include "Model/CleanInfo.h"

class DailyCleanProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit DailyCleanProxy(QObject *parent = 0);
    Q_INVOKABLE void queryDaily();
    Q_INVOKABLE void queryDailyRecord(QString Date);
    Q_INVOKABLE QString getData(int index, QString key);
    Q_INVOKABLE int getTaskNum();

    void clear();

protected slots:
    virtual void innerError(QSqlError &error);
    virtual void innerFinished(QSqlQueryEx query);

signals:
    void taskContentStandBy();
    void recordStandBy();

private:
    CleanInfo m_cleanInfo;
    QString   m_ClinicName;
};

#endif // DAILYCLEANPROXY_H
