#ifndef SterilizePROXY_H
#define SterilizePROXY_H
#include "SqlEvent.h"
#include "Model/SterilizeInfo.h"
#include <QDateTime>

class SterilizeProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit SterilizeProxy(QObject *parent = 0);
    void clear();

signals:
    void taskStandBy();
    void recordStandBy();
    void recordNotFound();
    void nextId(QString id);
    void noTask();
    void sigSucc();

public slots:
    void queryTask();
    void queryRecord(QString date);
    QString getData(int index, QString key);
    void sign(QString id,QString staffId, QString date, QString fileName);
    int  getNum();

protected slots:
    virtual void innerError(QSqlErrorEx &error);
    virtual void innerFinished(QSqlQueryEx query);

private:
    QString m_ClinicName;
    SterilizeInfo m_data;
};

#endif // SterilizePROXY_H
