#ifndef TRAININGPROXY_H
#define TRAININGPROXY_H

#include <QObject>
#include <Model/TrainingInfo.h>
#include <QDateTime>
#include "SqlEvent.h"
#include "Utilities/GlobalHelper.h"

class TrainingProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit TrainingProxy(QObject *parent = 0);
    Q_INVOKABLE void queryTraining(QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    Q_INVOKABLE int getTrainingNum();
    Q_INVOKABLE QString getTrainingInfo(int index, QString name);
    Q_INVOKABLE int getStaffNum();
    Q_INVOKABLE QString getSignInfo(int index, QString name);
signals:
    void trainingInfoStandBy();
public slots:

protected slots:
    void innerError(QSqlError & error);
    void innerFinished(QSqlQueryEx query);
private:
    void print();
    TrainingInfo m_trainingInfo;
    QString m_ClinicName;
    QSqlQueryEx m_lastQuery;
};

#endif // TRAININGPROXY_H
