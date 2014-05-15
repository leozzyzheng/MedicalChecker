#include "CheckProxy.h"

CheckProxy::CheckProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void CheckProxy::queryTask(int weekDay)
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    clear();

    m_currWeekDay = weekDay;

    QSqlQueryEx sql("select * from :ClinicName.:CheckTask");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":CheckTask",TABLE_CHECK_TASK);
    sql.setID("getTask");
    exec(sql);
}

void CheckProxy::queryRecord(QString date)
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    QSqlQueryEx sql("select * from :ClinicName.:CheckRecord where date_format(:CheckTime,'%Y-%m-%d') = ':dateTime'");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":CheckRecord",TABLE_CHECK_RECORD);
    sql.replaceHolder(":CheckTime",CHECK_TIME_TAG);
    sql.replaceHolder(":dateTime",date);
    sql.setID("getRecord");
    exec(sql);
}

int CheckProxy::getTaskNum()
{
    return m_checkInfo.size();
}

void CheckProxy::clear()
{
    m_checkInfo.clear();
}

void CheckProxy::innerError(QSqlError &error)
{
    emit this->error(error.text());
}

void CheckProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get Check information!");
        return;
    }

    if(query.size() <= 0)
    {
        if(query.getID() == "getRecord")
        {
            emit notChecked();
        }

        qDebug()<<"nothing find";
        return;
    }

    if(query.getID() == "getTask")
    {
        //int idNo = query.record().indexOf(CHECK_TASKID_TAG);
        int contentNo = query.record().indexOf(CHECK_CONTENT_TAG);
        int dayNo = query.record().indexOf(CHECK_DAY_TAG);

        if(//idNo == -1 ||
           contentNo == -1 ||
           dayNo == -1)
        {
            emit error("Check Data is Broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                QString day = query.record().value(dayNo).toString();
                QStringList dayList = day.split(",",QString::SkipEmptyParts);

                if(dayList.contains(QString::number(m_currWeekDay)))
                {
                    m_checkInfo.pushData(query.record().value(contentNo).toString());
                }
            }

            emit taskDataStandBy();
        }
    }
    else if(query.getID() == "getRecord")
    {
        emit isChecked();
    }
}
