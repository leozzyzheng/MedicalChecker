#include "TrainingProxy.h"

TrainingProxy::TrainingProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void TrainingProxy::queryTraining()
{
    QSqlQueryEx sql(QString("select * from clinic.TrainingHistory where ")+TRAINING_TIME_TAG+" ='" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "'");
    sql.setID("trainingInfo");
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

    if(query.getID() == "trainingInfo")
    {
        TrainingInfo::DataStruct data;
        int addrNo = query.record().indexOf(TRAINING_ADDR_TAG);
        int contentNo = query.record().indexOf(TRAINING_CONTENT_TAG);
        int staffNo = query.record().indexOf(TRAINING_STAFF_TAG);
        int submitNo = query.record().indexOf(TRAINING_SUBMIT_TAG);
        int timeNo = query.record().indexOf(TRAINING_TIME_TAG);
        int typeNo = query.record().indexOf(TRAINING_TYPE_TAG);
        int idNo = query.record().indexOf(TRAINING_TRAINID_TAG);

        if(addrNo == -1 ||
           contentNo == -1 ||
           staffNo == -1 ||
           submitNo == -1 ||
           timeNo == -1 ||
           typeNo == -1 ||
           idNo == -1)
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
            data.id = query.value(idNo).toString();

            m_trainingInfo.pushData(data);
        }

        QSqlQueryEx sql(QString("select * from clinic.TrainingRecord where ")+ TRAINING_TRAINID_TAG +" ='" + data.id + "'");
        sql.setID("signInfo");
        m_pSqlOp->exec(sql);

        emit trainingInfoStandBy();

        return;
    }
    else
    {
        int staffIdNo = query.record().indexOf(TRAINING_STAFFID_TAG);
        int staffSignNo = query.record().indexOf(TRAINING_STAFFSIGN_TAG);

        if(staffIdNo == -1 || staffSignNo == -1)
        {
            emit error("TrainingSign data is broken, please contact developer!");
            return;
        }

        while (query.next())
        {
            TrainingInfo::StaffSignInfo data;
            data.staffId = query.value(staffIdNo).toString();
            data.signature = query.value(staffSignNo).toString();
            m_trainingInfo.pushSignData(data);
        }

        emit completed();
    }
}
