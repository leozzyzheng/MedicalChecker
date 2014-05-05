#include "TrainingProxy.h"

TrainingProxy::TrainingProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void TrainingProxy::queryTraining()
{
    qDebug()<<"queryTraining";

    //QSqlQueryEx sql(QString("select * from clinica.TrainingHistory where ")+TRAINING_TIME_TAG+" ='" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm") + "'");
    QSqlQueryEx sql(QString("select * from clinica.TrainingHistory where ")+TRAINING_TIME_TAG+" ='2014-01-04 00:00:00'");
    sql.setID("trainingInfo");
    m_pSqlOp->exec(sql);
}

int TrainingProxy::getTrainingNum()
{
    return m_trainingInfo.trainingInfoSize();
}

QString TrainingProxy::getTrainingInfo(int index, QString name)
{
    return m_trainingInfo.getTrainingInfo(index, name);
}

int TrainingProxy::getStaffNum()
{
    return m_trainingInfo.trainingStaffSize();
}

QString TrainingProxy::getSignInfo(int index, QString name)
{
    return m_trainingInfo.getSignInfo(index, name);
}

void TrainingProxy::innerError(QSqlError error)
{
    qDebug()<<error.text();
    emit this->error("error");
}

void TrainingProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get training information!");
        return;
    }

    if(query.size() <= 0)
    {
        qDebug()<<"nothing find";
        return;
    }

    if(query.getID() == "trainingInfo")
    {
        std::map<QString,QString> data;
        int addrNo = query.record().indexOf(TRAINING_ADDR_TAG);
        int contentNo = query.record().indexOf(TRAINING_CONTENT_TAG);
        int staffNo = query.record().indexOf(TRAINING_STAFF_TAG);
        int timeNo = query.record().indexOf(TRAINING_TIME_TAG);
        int typeNo = query.record().indexOf(TRAINING_TYPE_TAG);
        int idNo = query.record().indexOf(TRAINING_TRAINID_TAG);

        if(addrNo == -1 ||
           contentNo == -1 ||
           staffNo == -1 ||
           timeNo == -1 ||
           typeNo == -1 ||
           idNo == -1)
        {
            emit error("Training data is broken, please contact developer!");
            return;
        }

        while (query.next())
        {
            data[TRAINING_ADDR_TAG] = query.value(addrNo).toString();
            data[TRAINING_CONTENT_TAG] = query.value(contentNo).toString();
            data[TRAINING_STAFF_TAG] = query.value(staffNo).toString();
            data[TRAINING_TIME_TAG] = query.value(timeNo).toString();
            data[TRAINING_TYPE_TAG] = query.value(typeNo).toString();
            data[TRAINING_TRAINID_TAG] = query.value(idNo).toString();

            m_trainingInfo.pushData(data);
        }

        QSqlQueryEx sql(QString("select * from clinica.TrainingRecord where ")+ TRAINING_TRAINID_TAG +" ='" + data[TRAINING_TRAINID_TAG] + "'");
        sql.setID("signInfo");
        m_pSqlOp->exec(sql);

        emit trainingInfoStandBy();

        return;
    }
    else
    {
        int staffIdNo = query.record().indexOf(TRAINING_STAFFID_TAG);
        int staffSignNo = query.record().indexOf(TRAINING_STAFFSIGN_TAG);
        int submitNo = query.record().indexOf(TRAINING_SUBMIT_TAG);
        int remarkNo = query.record().indexOf(TRAINING_REMARK_TAG);

        if(staffIdNo == -1 ||
           staffSignNo == -1 ||
           submitNo == -1 ||
           remarkNo == -1)
        {
            emit error("TrainingSign data is broken, please contact developer!");
            return;
        }

        while (query.next())
        {
            std::map<QString,QString> data;
            data[TRAINING_STAFFID_TAG] = query.value(staffIdNo).toString();
            data[TRAINING_STAFFSIGN_TAG] = query.value(staffSignNo).toString();
            data[TRAINING_SUBMIT_TAG] = query.value(submitNo).toString();
            data[TRAINING_REMARK_TAG] = query.value(remarkNo).toString();

            m_trainingInfo.pushSignData(data);
        }

        emit completed();

        print();
    }
}

void TrainingProxy::print()
{
    m_trainingInfo.print();
}
