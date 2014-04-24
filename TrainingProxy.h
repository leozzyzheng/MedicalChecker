#ifndef TRAININGPROXY_H
#define TRAININGPROXY_H

#include <QObject>
#include <Model/TrainingInfo.h>
#include <QDateTime>
#include "SqlEvent.h"

class TrainingProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit TrainingProxy(QObject *parent = 0);
    Q_INVOKABLE void queryTraining();
signals:

public slots:

protected slots:
    void innerError(QSqlError& error);
    void innerFinished(QSqlQuery & query);
private:
    TrainingInfo m_trainingInfo;
};

#endif // TRAININGPROXY_H
