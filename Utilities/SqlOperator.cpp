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
    connect(m_pSqlThread, SIGNAL(error(QSqlError,QSqlQueryEx*)),    this, SLOT(error(QSqlError,QSqlQueryEx*)),Qt::QueuedConnection);
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

const QSqlError SqlOperator::getLastError()
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

void SqlOperator::error(QSqlError error, QSqlQueryEx * sql)
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
    m_db.close();
}

void SqlThread::moveToOtherThread()
{
    moveToThread(ThreadSingleton::getInstance());
}

bool SqlThread::isOpen()
{
    return m_db.isOpen();
}

const QSqlError SqlThread::getLastError()
{
    return m_db.lastError();
}

void SqlThread::init()
{
    m_db = QSqlDatabase::addDatabase(DATABASE_TYPE);
    m_db.setHostName(DATABASE_HOSTNAME);
    m_db.setPort(DATABASE_PORT);
    m_db.setDatabaseName(DATABASE_DATABASENAME);
    m_db.setUserName(DATABASE_USERNAME);
    m_db.setPassword(DATABASE_PASSWD);

    m_status = DATABASE_CONNECTING;

    if (!m_db.open())
    {
        qDebug()<<m_db.lastError().text();
        m_status = DATABASE_CONNECTED_FAIL;
        m_dbError = m_db.lastError();
        return;
    }
    else
    {
        qDebug()<<"Successful open database :" << m_db.databaseName() <<"!";
        m_status = DATABASE_CONNECTED_SUCC;
    }

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
    if(!sql->exec(sql->getSqlString()))
    {
        qDebug()<<"     basic query done";
        QSqlError err(sql->lastError());
        emit error(err,sql);
    }
    else
    {
        qDebug()<<"     basic query done";
        emit result(sql);
    }
}
