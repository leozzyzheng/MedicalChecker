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
public slots:
     void queryTraining(QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
     void queryTrainingStaff(QString trainingId);
     int getTrainingNum();
     QString getTrainingInfo(int index, QString name);
     int getStaffNum();
     QString getSignInfo(int index, QString name);
     void sign(QString trId, QString staffId, QString sig, QString date);
signals:
    void trainingInfoStandBy();
    void staffInfoStandBy();
    void clear();
    void clearSignInfo();
    void updateSucc();
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
