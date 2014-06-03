#include "SqlOperator.h"

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

    connect(m_pSqlThread, SIGNAL(result(QSqlQueryEx*)),             this, SLOT(result(QSqlQueryEx*)),Qt::QueuedConnection);
    connect(m_pSqlThread, SIGNAL(error(QSqlErrorEx,QSqlQueryEx*)),    this, SLOT(error(QSqlErrorEx,QSqlQueryEx*)),Qt::QueuedConnection);
    connect(this,         SIGNAL(innerExec(QSqlQueryEx *)),         m_pSqlThread, SLOT(exec(QSqlQueryEx *)),Qt::QueuedConnection);
    connect(this,         SIGNAL(threadInit()),                     m_pSqlThread, SLOT(init()));

    m_pSqlThread->moveToOtherThread();

    emit threadInit();

    qDebug()<<"Init Complete";
}

bool SqlOperator::isOpen()
{
    return m_pSqlThread->isOpen();
}

const QSqlErrorEx SqlOperator::getLastError()
{
    return m_pSqlThread->getLastError();
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


SqlThread::SqlThread()
{
    m_status = DATABASE_NOCONNECTING;
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
    //return m_db.isOpen();
    return true;
}

const QSqlErrorEx SqlThread::getLastError()
{
    return QSqlErrorEx("no Error");
}

void SqlThread::init()
{
    connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  this,       SLOT(deleteLater()));
}

void SqlThread::exec(QSqlQueryEx * sql)
{
    if(!sql->getExecutable())
    {
        delete sql;
        sql = NULL;
        return;
    }

    qDebug()<<"     basic query";
    if(!sql->exec())
    {
        qDebug()<<"     basic query done and found error";
        emit error(sql->error(),sql);
    }
    else
    {
        qDebug()<<"     basic query done succ";
        emit result(sql);
    }
}
