#include "SterilizeProxy.h"

SterilizeProxy::SterilizeProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void SterilizeProxy::clear()
{
    m_data.clear();
}

void SterilizeProxy::queryTask()
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    clear();

    QSqlQueryEx sql("Select * from :ClinicName.SterilizeTask order by :STime");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":STime",STER_STIME_TAG);
    sql.setID("task");
    exec(sql);
}

void SterilizeProxy::queryRecord(QString date)
{
//    QString startTime;
//    QString endTime;
//    QString id;
//    qint64 now = QDateTime::fromString(date,"HH:mm:ss").toMSecsSinceEpoch();

//    int num = m_data.getNum();

//    if(num == 0)
//    {
//        emit noTask();
//        return;
//    }

//    for(int i = 0; i < num; ++i)
//    {
//        QString sTime = m_data.getData(i,STER_STIME_TAG);
//        QString eTime = m_data.getData(i,STER_ETIME_TAG);

//        qint64 s = QDateTime::fromString(sTime,"HH:mm:ss").toMSecsSinceEpoch();
//        qint64 e = QDateTime::fromString(eTime,"HH:mm:ss").toMSecsSinceEpoch();

//        if(now >= s && now <= e)
//        {
//            startTime = sTime;
//            endTime = eTime;
//            id = m_data.getData(i,STER_TASKID_TAG);
//            break;
//        }
//        else if(now < s)
//        {
//            startTime = sTime;
//            endTime = eTime;
//            id = m_data.getData(i,STER_TASKID_TAG);
//        }
//        else if(now > e)
//        {
//            //do nothing
//        }
//    }

//    if(startTime.isEmpty())
//    {
//        emit completed();
//        return;
//    }
//    else
//    {
//        emit nextId(id);
//    }

//    startTime = QDateTime::currentDateTime().toString("yyyy-MM-dd ")+startTime;
//    endTime = QDateTime::currentDateTime().toString("yyyy-MM-dd ")+endTime;

//    QSqlQueryEx sql("Select * from :ClinicName.SterilizeRecord where unix_timestamp(:time) between unix_timestamp(':stime') and unix_timestamp(':etime')");
//    sql.replaceHolder(":ClinicName",m_ClinicName);
//    sql.replaceHolder(":time",STER_CHECKTIME_TAG);
//    sql.replaceHolder(":stime",startTime);
//    sql.replaceHolder(":etime",endTime);
//    sql.setID("record");
//    exec(sql);

    QSqlQueryEx sql("Select * from :ClinicName.SterilizeRecord where date_format(:time,'%Y-%m-%d') = ':dateTime' order by CheckTime");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":time",STER_CHECKTIME_TAG);
    sql.replaceHolder(":dateTime",date);
    sql.setID("record");
    exec(sql);
}

QString SterilizeProxy::getData(int index, QString key)
{
    return m_data.getData(index,key);
}

void SterilizeProxy::sign(QString id, QString staffId, QString date, QString fileName)
{
    QSqlQueryEx sql("insert into :ClinicName.SterilizeRecord values(:taskId,':staffId',':date',':sig')");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":taskId",id.toInt());
    sql.replaceHolder(":staffId",staffId);
    sql.replaceHolder(":date",date);
    sql.replaceHolder(":sig",fileName);
    sql.setID("update");
    exec(sql);
}

int SterilizeProxy::getNum()
{
    return m_data.getNum();
}

void SterilizeProxy::innerError(QSqlErrorEx &error)
{
    emit this->error(error.text());
}

void SterilizeProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get Sterilize information!");
        return;
    }

    if(query.numRowsAffected() <=0 && query.size() <= 0)
    {
        qDebug()<<"ster nothing find";

        if(query.getID() == "record")
        {
            emit recordStandBy();
        }
        else if(query.getID() == "task")
        {
            emit noTask();
        }

        return;
    }

    if(query.getID() == "task")
    {
        int idNo = query.record().indexOf(STER_TASKID_TAG);
        int stimeNo = query.record().indexOf(STER_STIME_TAG);
        int etimeNo = query.record().indexOf(STER_ETIME_TAG);
        int inVenNo = query.record().indexOf(STER_INVEN_TAG);
        int contentNo = query.record().indexOf(CLEAN_TASKCONTENT_TAG);

        if(idNo == -1||
           stimeNo == -1||
           etimeNo == -1||
           inVenNo == -1||
           contentNo == -1)
        {
            emit error("Sterilize data broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                std::map<QString,QString> data;
                data[STER_TASKID_TAG] = query.value(idNo).toString();
                data[CLEAN_TASKCONTENT_TAG] = query.value(contentNo).toString();
                data[STER_STIME_TAG] = query.value(stimeNo).toDateTime().toString("HH:mm:ss");
                data[STER_ETIME_TAG] = query.value(etimeNo).toDateTime().toString("HH:mm:ss");
                data[STER_INVEN_TAG] = query.value(inVenNo).toString();
                m_data.setData(data, query.value(idNo).toString());
            }

            emit taskStandBy();
        }
    }
    else if(query.getID() == "record")
    {
        int idNo = query.record().indexOf(STER_TASKID_TAG);
        int staffNo = query.record().indexOf(STER_SIG_TAG);
        int timeNo  =  query.record().indexOf(STER_CHECKTIME_TAG);

        if(idNo == -1||
           staffNo == -1||
           timeNo == -1)
        {
            emit error("Sterilize record broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                std::map<QString,QString> data;
                QString id = query.value(idNo).toString();
                data[STER_SIG_TAG] = query.value(staffNo).toString();
                data[STER_CHECKTIME_TAG] = query.value(timeNo).toDateTime().toString("HH:mm:ss");
                m_data.setRecordData(data,id);
            }

            emit recordStandBy();
        }
    }
    else if(query.getID() == "update")
    {
        emit sigSucc();
    }
}
