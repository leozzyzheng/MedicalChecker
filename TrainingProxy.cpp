#include "TrainingProxy.h"

TrainingProxy::TrainingProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void TrainingProxy::queryTraining(QString dateTime)
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    m_trainingInfo.clear();
    emit clear();

    qDebug()<<m_ClinicName;

    QSqlQueryEx sql("select * from :clinicName.TrainingHistory where date_format(:trainingTime,'%Y-%m-%d') = ':dateTime'");
    sql.replaceHolder(":clinicName",m_ClinicName);
    sql.replaceHolder(":trainingTime",TRAINING_TIME_TAG);
    sql.replaceHolder(":dateTime",dateTime);

    qDebug()<<sql.getSqlString();

    sql.setID("trainingInfo");
    exec(sql);
}

void TrainingProxy::queryTrainingStaff(QString trainingId)
{
    m_trainingInfo.clearSignInfo();
    emit clearSignInfo();

    QSqlQueryEx sql("select User.:staffName,"
                    "TrainingRecord.:staffId,"
                    "TrainingRecord.:trainingIdTag,"
                    "TrainingRecord.:isSign_In,"
                    "TrainingRecord.:submitTime,"
                    "TrainingRecord.:remark "
                    "from :clinicName.TrainingRecord,:clinicName.User "
                    "where TrainingRecord.:trainingIdTag = ':id' and User.:userId = TrainingRecord.:staffId"
                    );

    sql.replaceHolder(":staffName",USER_NAME_TAG);
    sql.replaceHolder(":staffId",TRAINING_STAFFID_TAG);
    sql.replaceHolder(":isSign_In",TRAINING_STAFFSIGN_TAG);
    sql.replaceHolder(":submitTime",TRAINING_SUBMIT_TAG);
    sql.replaceHolder(":remark",TRAINING_REMARK_TAG);
    sql.replaceHolder(":clinicName",m_ClinicName);
    sql.replaceHolder(":trainingIdTag",TRAINING_TRAINID_TAG);
    sql.replaceHolder(":id",trainingId);
    sql.replaceHolder(":userId",USER_NUMBERID_TAG);
    sql.setID("signInfo");
    qDebug()<<sql.getSqlString();
    exec(sql);
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

void TrainingProxy::sign(QString trId, QString staffId, QString sig, QString date)
{
    QSqlQueryEx sql("update :clinicName.TrainingRecord set :sigTag = ':sigValue',:subtime = ':date' where :staffIdTag = ':staffid' and :trIdTag = ':trid'");
    sql.replaceHolder(":clinicName",m_ClinicName);
    sql.replaceHolder(":sigTag",TRAINING_STAFFSIGN_TAG);
    sql.replaceHolder(":sigValue",sig);
    sql.replaceHolder(":subtime",TRAINING_SUBMIT_TAG);
    sql.replaceHolder(":date",date);
    sql.replaceHolder(":staffIdTag",TRAINING_STAFFID_TAG);
    sql.replaceHolder(":staffid",staffId);
    sql.replaceHolder(":trIdTag",TRAINING_TRAINID_TAG);
    sql.replaceHolder(":trid",trId);
    sql.setID("updateSig");
    qDebug()<<sql.getSqlString();
    exec(sql);
}

void TrainingProxy::innerError(QSqlError & error)
{
    emit this->error(error.text());
}

void TrainingProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get training information!");
        return;
    }

    if(query.numRowsAffected() <=0 && query.size() <= 0)
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
            qDebug()<<query.value(timeNo).typeName();
            data[TRAINING_ADDR_TAG] = query.value(addrNo).toString();
            data[TRAINING_CONTENT_TAG] = query.value(contentNo).toString();
            data[TRAINING_STAFF_TAG] = query.value(staffNo).toString();
            data[TRAINING_TIME_TAG] = query.value(timeNo).toDateTime().toString("yyyy-MM-dd HH:mm:ss");
            data[TRAINING_TYPE_TAG] = query.value(typeNo).toString();
            data[TRAINING_TRAINID_TAG] = query.value(idNo).toString();

            m_trainingInfo.pushData(data);
        }

        emit trainingInfoStandBy();

        return;
    }
    else if(query.getID() == "signInfo")
    {
        int staffIdNo = query.record().indexOf(TRAINING_STAFFID_TAG);
        int staffSignNo = query.record().indexOf(TRAINING_STAFFSIGN_TAG);
        int submitNo = query.record().indexOf(TRAINING_SUBMIT_TAG);
        int remarkNo = query.record().indexOf(TRAINING_REMARK_TAG);
        int nameNo = query.record().indexOf(USER_NAME_TAG);

        if(staffIdNo == -1 ||
           staffSignNo == -1 ||
           submitNo == -1 ||
           remarkNo == -1 ||
           nameNo == -1)
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
            data[USER_NAME_TAG] = query.value(nameNo).toString();
            m_trainingInfo.pushSignData(data);
        }

        emit staffInfoStandBy();

        //print();
    }
    else if(query.getID() == "updateSig")
    {
        emit updateSucc();
    }
}

void TrainingProxy::print()
{
    m_trainingInfo.print();
}
