#include "TrainingProxy.h"

TrainingProxy::TrainingProxy(QObject *parent) :
    SqlEvent(parent)
{
}

void TrainingProxy::innerError(QSqlError &error)
{

}

void TrainingProxy::innerFinished(QSqlQuery &query)
{

}
