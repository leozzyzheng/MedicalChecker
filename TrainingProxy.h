#ifndef TRAININGPROXY_H
#define TRAININGPROXY_H

#include <QObject>
#include <Model/TrainingInfo.h>
#include "SqlEvent.h"

class TrainingProxy : public SqlEvent
{
    Q_OBJECT
public:
    explicit TrainingProxy(QObject *parent = 0);

signals:

public slots:

protected slots:
    void innerError(QSqlError& error);
    void innerFinished(QSqlQuery & query);

};

#endif // TRAININGPROXY_H
