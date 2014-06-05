#include "DailyCleanProxy.h"

DailyCleanProxy::DailyCleanProxy(QObject *parent):
    SqlEvent(parent)
{

}

void DailyCleanProxy::queryDaily()
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    clear();

    QSqlQueryEx sql("select * from :ClinicName.:DailyTableTag");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":DailyTableTag",TABLE_DAILY_CLEAN_TASK);
    sql.setID("getTask");
    exec(sql);
}

void DailyCleanProxy::queryDailyRecord(QString Date)
{
    QSqlQueryEx sql("select * from :ClinicName.:DailyRecord where date_format(:CleanTime,'%Y-%m-%d') = ':Date'");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":DailyRecord",TABLE_DAILY_CLEAN_RECORD);
    sql.replaceHolder(":CleanTime",DAILYCLEAN_TIME_TAG);
    sql.replaceHolder(":Date",Date);
    sql.setID("getRecord");
    exec(sql);
}

QString DailyCleanProxy::getData(int index, QString key)
{
    return m_cleanInfo.getData(index, key);
}

int DailyCleanProxy::getTaskNum()
{
    return m_cleanInfo.getContentTableSize();
}

void DailyCleanProxy::sign(QString taskContent, QString cleanTime, QString staffId, QString sig)
{
    qDebug()<<taskContent;
    QSqlQueryEx sql("insert into :ClinicName.:DailyCleanRecord values(:id,':time',':staffid',':sig')");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":DailyCleanRecord",TABLE_DAILY_CLEAN_RECORD);
    sql.replaceHolder(":id",QString::number(m_cleanInfo.getIdFromContent(taskContent)));
    sql.replaceHolder(":time",cleanTime);
    sql.replaceHolder(":staffid",staffId);
    sql.replaceHolder(":sig",sig);
    sql.setID("insertRecord");
    qDebug()<<sql.getSqlString();
    exec(sql);
}

void DailyCleanProxy::clear()
{
    m_cleanInfo.clear();
}

void DailyCleanProxy::innerError(QSqlErrorEx &error)
{
    emit this->error(error.text());
}

void DailyCleanProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get DailyClean information!");
        return;
    }

    if(query.numRowsAffected() <= 0 && query.size() <= 0)
    {
        qDebug()<<"nothing find";

        if(query.getID() == "getRecord")
        {
            emit recordStandBy();
        }

        return;
    }

    if(query.getID() == "getTask")
    {
        int idNo = query.record().indexOf(DAILYCLEAN_TASKID_TAG);
        int contentNo = query.record().indexOf(CLEAN_TASKCONTENT_TAG);
        int staffIdNo = query.record().indexOf(CLEAN_STAFFID_TAG);

        if(idNo == -1||
           contentNo == -1||
           staffIdNo == -1)
        {
            emit this->error("DailyClean Task Data is Broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                int index = query.record().value(idNo).toInt();
                m_cleanInfo.pushId(index);
                m_cleanInfo.setContentTableData(index, query.record().value(contentNo).toString());
                m_cleanInfo.setStaffTableData(index, query.record().value(staffIdNo).toString());
                m_cleanInfo.setData(index,CLEAN_TASKCONTENT_TAG, query.record().value(contentNo).toString());
                m_cleanInfo.setData(index,CLEAN_STAFFID_TAG, query.record().value(staffIdNo).toString());
            }

            emit taskContentStandBy();
        }
    }
    else if(query.getID() == "getRecord")
    {
        int idNo = query.record().indexOf(DAILYCLEAN_TASKID_TAG);
        int timeNo = query.record().indexOf(DAILYCLEAN_TIME_TAG);
        int sigNo = query.record().indexOf(CLEAN_SIG_TAG);
        int staffNo = query.record().indexOf(CLEAN_SIGNSTAFFID_TAG);

        if(idNo == -1||
           timeNo == -1||
           sigNo == -1 ||
           staffNo == -1)
        {
            emit this->error("DailyRecord Data is Broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                std::map<QString,QString> data;
                int index = query.record().value(idNo).toInt();
                data[DAILYCLEAN_TIME_TAG] = query.record().value(timeNo).toString();
                data[CLEAN_SIG_TAG] = query.record().value(sigNo).toString();
                data[CLEAN_TASKCONTENT_TAG] = m_cleanInfo.getContentData(index);

                QString signId = query.record().value(staffNo).toString();

                if(signId.isEmpty())
                    data[CLEAN_STAFFID_TAG] = m_cleanInfo.getStaffData(index);
                else
                    data[CLEAN_STAFFID_TAG] = signId;

                qDebug()<<"sig"<<data[CLEAN_SIG_TAG];

                m_cleanInfo.setData(index, data);
            }

            emit recordStandBy();
        }
    }
    else if(query.getID() == "insertRecord")
    {
        emit updateSucc();
    }

}
