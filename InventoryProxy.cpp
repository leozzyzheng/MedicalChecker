#include "InventoryProxy.h"

InventoryProxy::InventoryProxy(QObject *parent):
    SqlEvent(parent)
{
}

void InventoryProxy::clear()
{
    m_data.clear();
}

void InventoryProxy::update()
{
    m_ClinicName = GlobalHelper::getGlobalValue("ClinicName");

    if(m_ClinicName.isEmpty())
    {
        qDebug()<<"Critical Error! No ClinicName but Logined!";
        return;
    }

    clear();

    QSqlQueryEx sql("select * from :Clinic.Inventory");
    sql.replaceHolder(":Clinic",m_ClinicName);
    sql.setID("update");
    exec(sql);
}

int InventoryProxy::getNum(int id)
{
    return m_data.getNum(id);
}

QString InventoryProxy::getName(int id)
{
    return m_data.getName(id);
}

void InventoryProxy::innerError(QSqlError &error)
{
    emit this->error(error.text());
}

void InventoryProxy::innerFinished(QSqlQueryEx query)
{
    if(!query.isActive())
    {
        emit error("Cannot get Inventory information!");
        return;
    }

    if(query.numRowsAffected() <=0 && query.size() <= 0)
    {
        qDebug()<<"nothing find";
        return;
    }

    if(query.getID() == "update")
    {
        int idNo = query.record().indexOf(INVEN_ID_TAG);
        int nameNo = query.record().indexOf(INVEN_NAME_TAG);
        int numNo = query.record().indexOf(INVEN_NUM_TAG);

        if(idNo == -1 ||
           nameNo == -1||
           numNo == -1)
        {
            emit error("Inventory data broken!");
            return;
        }
        else
        {
            while(query.next())
            {
                int id = query.value(idNo).toInt();
                QString name = query.value(nameNo).toString();
                int num = query.value(numNo).toInt();
                m_data.setData(id,name,num);
            }

            emit completed();
        }
    }

}
