#include "UserProxy.h"

UserProxy::UserProxy(QObject *parent):
    SqlEvent(parent)
{
}

void UserProxy::queryUser()
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    clear();

    QSqlQueryEx sql("select * from :ClinicName.:UserTag");
    sql.replaceHolder(":ClinicName",m_ClinicName);
    sql.replaceHolder(":UserTag",TABLE_USER);
    sql.setID("getUser");
    exec(sql);
}

QString UserProxy::getData(QString idnumber, QString key)
{
    return m_userInfo.getData(idnumber,key);
}

void UserProxy::prepareName(QString staffId)
{
    m_userInfo.prepareName(staffId);
}

QString UserProxy::getUserName(int index)
{
    return m_userInfo.getUserName(index);
}

QString UserProxy::getUserId(int index)
{
    return m_userInfo.getUserId(index);
}

int UserProxy::nameSize()
{
    return m_userInfo.nameSize();
}

void UserProxy::clear()
{
    m_userInfo.clear();
}

void UserProxy::innerError(QSqlErrorEx &error)
{
    emit this->error(error.text());
}

void UserProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get User information!");
        return;
    }

    if(query.numRowsAffected() <=0 && query.size() <= 0)
    {
        qDebug()<<"nothing find";
        return;
    }

    if(query.getID() == "getUser")
    {
        int nameNo = query.record().indexOf(USER_NAME_TAG);
        int idNo = query.record().indexOf(USER_NUMBERID_TAG);

        if(nameNo == -1||
           idNo == -1)
        {
            emit error("User Data is Broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                std::map<QString,QString> data;
                QString idnumber = query.value(idNo).toString();
                data[USER_NAME_TAG] = query.value(nameNo).toString();
                m_userInfo.setData(idnumber,data);
            }

            emit userDataStandBy();
        }
    }
}
