#include "WeeklyCleanProxy.h"

WeeklyCleanProxy::WeeklyCleanProxy(QObject *parent):
    SqlEvent(parent)
{

}

void WeeklyCleanProxy::queryWeekly()
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    clear();

    QSqlQueryEx sql("select * from :ClinicName.:WeeklyTask");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":WeeklyTask",TABLE_WEEKLY_CLEAN_TASK);
    sql.setID("getTask");
    exec(sql);
}

void WeeklyCleanProxy::queryRecord(QString weekNum)
{
    QSqlQueryEx sql("select * from :ClinicName.:Record where :Week = :weekNum");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":Record",TABLE_WEEKLY_CLEAN_RECORD);
    sql.replaceHolder(":Week",WEEKLYCLEAN_TIME_TAG);
    sql.replaceHolder(":weekNum",weekNum);
    sql.setID("getRecord");
    exec(sql);
}

int WeeklyCleanProxy::getTaskNum()
{
    return m_cleanInfo.getContentTableSize();
}

QString WeeklyCleanProxy::getData(int index, QString key)
{
    return m_cleanInfo.getData(index,key);
}

void WeeklyCleanProxy::sign(QString taskContent, int week, QString staffId, QString sig)
{
    QSqlQueryEx sql("insert into :ClinicName.:WeeklyCleanRecord values(:id,:weekNum,':staffid',':sig')");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":WeeklyCleanRecord",TABLE_WEEKLY_CLEAN_RECORD);
    sql.replaceHolder(":id",QString::number(m_cleanInfo.getIdFromContent(taskContent)));
    sql.replaceHolder(":weekNum",QString::number(week));
    sql.replaceHolder(":staffid",staffId);
    sql.replaceHolder(":sig",sig);
    sql.setID("insertRecord");
    exec(sql);
}

void WeeklyCleanProxy::clear()
{
    m_cleanInfo.clear();
}

void WeeklyCleanProxy::innerError(QSqlErrorEx &error)
{
    emit this->error(error.text());
}

void WeeklyCleanProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get WeeklyClean information!");
        return;
    }

    if(query.numRowsAffected() <=0 && query.size() <= 0)
    {
        qDebug()<<"nothing find";

        if(query.getID() == "getRecord")
        {
            emit recordDataStandBy();
        }

        return;
    }

    if(query.getID() == "getTask")
    {
        int idNo = query.record().indexOf(WEEKLYCLEAN_TASKID_TAG);
        int contentNo = query.record().indexOf(CLEAN_TASKCONTENT_TAG);
        int staffNo = query.record().indexOf(CLEAN_STAFFID_TAG);

        if(idNo == -1 ||
           contentNo == -1 ||
           staffNo == -1)
        {
            emit error("WeeklyClean Data is Broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                int index = query.record().value(idNo).toInt();
                m_cleanInfo.pushId(index);
                m_cleanInfo.setContentTableData(index, query.record().value(contentNo).toString());
                m_cleanInfo.setStaffTableData(index, query.record().value(staffNo).toString());
                m_cleanInfo.setData(index,CLEAN_TASKCONTENT_TAG, query.record().value(contentNo).toString());
                m_cleanInfo.setData(index,CLEAN_STAFFID_TAG, query.record().value(staffNo).toString());
            }

            emit taskDataStandBy();
        }
    }
    else if(query.getID() == "getRecord")
    {
        int idNo = query.record().indexOf(WEEKLYCLEAN_TASKID_TAG);
        int weekNo = query.record().indexOf(WEEKLYCLEAN_TIME_TAG);
        int sigNo = query.record().indexOf(CLEAN_SIG_TAG);
        int staffNo = query.record().indexOf(CLEAN_SIGNSTAFFID_TAG);

        if(idNo == -1 ||
           weekNo == -1 ||
           sigNo == -1 ||
           staffNo == -1)
        {
            emit error("WeeklyClean Data is Broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                std::map<QString,QString> data;
                int index = query.record().value(idNo).toInt();
                data[WEEKLYCLEAN_TIME_TAG] = query.record().value(weekNo).toString();
                data[CLEAN_SIG_TAG] = query.record().value(sigNo).toString();
                data[CLEAN_TASKCONTENT_TAG] = m_cleanInfo.getContentData(index);
                QString signId = query.record().value(staffNo).toString();

                if(signId.isEmpty())
                    data[CLEAN_STAFFID_TAG] = m_cleanInfo.getStaffData(index);
                else
                    data[CLEAN_STAFFID_TAG] = signId;

                m_cleanInfo.setData(index, data);
            }

            emit recordDataStandBy();
        }
    }
    else if(query.getID() == "insertRecord")
    {
        emit updateSucc();
    }
}
