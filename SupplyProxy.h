#ifndef SUPPLYPROXY_H
#define SUPPLYPROXY_H

#include "SqlEvent.h"
#include "Model/CleanInfo.h"

class SupplyProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit SupplyProxy(QObject *parent = 0);
public slots:
     void querySupply();
     void queryRecord(QString date);
     int  getTaskNum();
     QString getData(int index, QString key);
     void sign(QString taskContent, QString cleanTime, QString staffId, QString sig);

    void clear();

signals:
    void taskDataStandBy();
    void recordDataStandBy();
    void updateSucc();
public slots:

private slots:
    virtual void innerError(QSqlError &error);
    virtual void innerFinished(QSqlQueryEx query);

private:
    CleanInfo m_cleanInfo;
    QString m_ClinicName;
};

#endif // SUPPLYPROXY_H
