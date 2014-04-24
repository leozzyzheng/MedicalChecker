#include "TrainingProxy.h"

TrainingProxy::TrainingProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void TrainingProxy::queryTraining()
{
    QString sql = "select * from clinic.TrainingHistory where trainingTime ='" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "'";
    m_pSqlOp->exec(sql);
}

void TrainingProxy::innerError(QSqlError &error)
{
    emit this->error("error");
}

void TrainingProxy::innerFinished(QSqlQuery &query)
{
    if(!query.isActive())
    {
        emit error("Cannot get training information!");
        return;
    }

    while (query.next())
    {

    }



    emit completed();
}
