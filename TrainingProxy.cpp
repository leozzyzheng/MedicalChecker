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

void TrainingProxy::innerFinished(QSqlQueryEx &query)
{
    if(!query.isActive())
    {
        emit error("Cannot get training information!");
        return;
    }

    TrainingInfo::DataStruct data;
    int addrNo = query.record().indexOf(TRAINING_ADDR_TAG);
    int contentNo = query.record().indexOf(TRAINING_CONTENT_TAG);
    int staffNo = query.record().indexOf(TRAINING_STAFF_TAG);
    int submitNo = query.record().indexOf(TRAINING_SUBMIT_TAG);
    int timeNo = query.record().indexOf(TRAINING_TIME_TAG);
    int typeNo = query.record().indexOf(TRAINING_TYPE_TAG);

    if(addrNo == -1 ||
       contentNo == -1 ||
       staffNo == -1 ||
       submitNo == -1 ||
       timeNo == -1 ||
       typeNo == -1)
    {
        emit error("Training data is broken, please contact developer!");
        return;
    }

    while (query.next())
    {
        data.addr = query.value(addrNo).toString();
        data.content = query.value(contentNo).toString();
        data.staff= query.value(staffNo).toString();
        data.submitTime = query.value(submitNo).toString();
        data.time = query.value(timeNo).toString();
        data.type = query.value(typeNo).toString();
    }



    emit completed();
}
