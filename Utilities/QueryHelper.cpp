#include "QueryHelper.h"

QueryHelper::QueryHelper(QObject *parent):
    QObject(parent)
{

}

void QueryHelper::emitResult(QSqlQueryEx *pQuery)
{
    emit result(pQuery);
}

void QueryHelper::emitError(QSqlError &error, QSqlQueryEx *pQuery)
{
    emit this->error(error,pQuery);
}
