#ifndef SUPPLYPROXY_H
#define SUPPLYPROXY_H

#include "SqlEvent.h"
#include "Model/CleanInfo.h"

class SupplyProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit SupplyProxy(QObject *parent = 0);
    Q_INVOKABLE void querySupply();
    Q_INVOKABLE void queryRecord(QString date);
    Q_INVOKABLE int  getTaskNum();
    Q_INVOKABLE QString getData(int index, QString key);

    void clear();

signals:
    void taskDataStandBy();
    void recordDataStandBy();
public slots:

private slots:
    virtual void innerError(QSqlError &error);
    virtual void innerFinished(QSqlQueryEx query);

private:
    CleanInfo m_cleanInfo;
    QString m_ClinicName;
};

#endif // SUPPLYPROXY_H
