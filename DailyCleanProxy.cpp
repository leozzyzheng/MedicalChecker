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
    QSqlQueryEx sql("select * from :ClinicName.:DailyRecord where :CleanTime = ':Date'");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":DailyRecord",TABLE_DAILY_CLEAN_RECORD);
    sql.replaceHolder(":CleanTime",DAILYCLEAN_CLEANTIME_TAG);
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

void DailyCleanProxy::clear()
{
    m_cleanInfo.clear();
}

void DailyCleanProxy::innerError(QSqlError &error)
{
    emit this->error(error.text());
}

void DailyCleanProxy::innerFinished(QSqlQueryEx query)
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

    if(query.getID() == "getTask")
    {
        int idNo = query.record().indexOf(DAILYCLEAN_TASKID_TAG);
        int contentNo = query.record().indexOf(CLEAN_TASKCONTENT_TAG);
        int staffIdNo = query.record().indexOf(CLEAN_STAFFID_TAG);

        if(idNo == -1||
           contentNo == -1||
           staffIdNo == -1)
        {
            emit this->error("DailyCleanTask Data is Broken!");
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
            }

            emit taskContentStandBy();
        }
    }
    else if(query.getID() == "getRecord")
    {
        int idNo = query.record().indexOf(DAILYCLEAN_TASKID_TAG);
        int timeNo = query.record().indexOf(DAILYCLEAN_CLEANTIME_TAG);
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
                data[DAILYCLEAN_CLEANTIME_TAG] = query.record().value(timeNo).toString();
                data[CLEAN_SIG_TAG] = query.record().value(sigNo).toString();
                data[CLEAN_TASKCONTENT_TAG] = m_cleanInfo.getContentData(index);

                QString signId = query.record().value(staffNo).toString();

                if(signId.isEmpty())
                    data[CLEAN_STAFFID_TAG] = m_cleanInfo.getStaffData(index);
                else
                    data[CLEAN_STAFFID_TAG] = signId;

                m_cleanInfo.setData(index, data);
            }

            emit recordStandBy();
        }
    }

}
