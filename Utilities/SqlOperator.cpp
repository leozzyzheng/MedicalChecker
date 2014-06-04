#include "SqlOperator.h"

SqlThread::SqlThread():
    QObject(0)
{
}

SqlThread::~SqlThread()
{
}

void SqlThread::moveToOtherThread()
{
    moveToThread(ThreadSingleton::getInstance());
}

bool SqlThread::isOpen()
{
    return true;
}

void SqlThread::init(SqlOperator * self)
{
    connect(this, SIGNAL(innerresult(QSqlQueryEx*)),             self, SLOT(result(QSqlQueryEx*)));
    connect(this, SIGNAL(innererror(QSqlErrorEx,QSqlQueryEx*)),  self, SLOT(error(QSqlErrorEx,QSqlQueryEx*)));
    connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  this,       SLOT(deleteLater()));
}

void SqlThread::exec(QSqlQueryEx * sql)
{
    qDebug()<<"     basic query";

    if(!sql->getExecutable())
    {
        delete sql;
        sql = NULL;
        qDebug()<<"     basic query canceled.";
        return;
    }

    if(!sql->exec())
    {
        qDebug()<<"     basic query done and found error";
        emit innererror(sql->error(),sql);
    }
    else
    {
        qDebug()<<"     basic query done succ";
        emit innerresult(sql);
    }

    qDebug()<<"     basic query return";
}

SqlOperator::~SqlOperator()
{
    m_pSqlThread->deleteLater();
}

void SqlOperator::Init()
{
    qDebug()<<"Init";

    if(!m_pSqlThread)
    {
        delete m_pSqlThread;
    }

    m_pSqlThread = new SqlThread();
    m_pSqlThread->moveToOtherThread();
    m_pSqlThread->setParent(0);

    connect(this,         SIGNAL(innerExec(QSqlQueryEx *)),             m_pSqlThread, SLOT(exec(QSqlQueryEx *)));
    connect(this,         SIGNAL(threadInit(SqlOperator *)),            m_pSqlThread, SLOT(init(SqlOperator *)));

    emit threadInit(this);

    qDebug()<<"Init Complete";
}

bool SqlOperator::isOpen()
{
    return m_pSqlThread->isOpen();
}

SqlOperator::SqlOperator()
{
    m_pSqlThread = NULL;
}

//do not use it!!!
void SqlOperator::exec(QSqlQueryEx * sql)
{
    emit innerExec(sql);
}

void SqlOperator::result(QSqlQueryEx * result)
{
    result->emitResult();
    qDebug()<<"delete r";
    delete result;
    result = NULL;
}

void SqlOperator::error(QSqlErrorEx error, QSqlQueryEx * sql)
{
    sql->emitError(error);
    qDebug()<<"delete e";
    delete sql;
    sql = NULL;
}
