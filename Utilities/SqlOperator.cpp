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

    connect(m_pSqlThread, SIGNAL(result(QSqlQueryEx*)),             this, SLOT(result(QSqlQueryEx*)));
    connect(m_pSqlThread, SIGNAL(error(QSqlError,QSqlQueryEx*)),    this, SLOT(error(QSqlError,QSqlQueryEx*)));
    connect(this,         SIGNAL(innerExec(QSqlQueryEx *)),         m_pSqlThread, SLOT(exec(QSqlQueryEx *)));
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
    delete result;
    result = NULL;
}

void SqlOperator::error(QSqlError error, QSqlQueryEx * sql)
{
    sql->emitError(error);
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
//    while(m_status != DATABASE_CONNECTED_SUCC)
//    {
//        if(m_status == DATABASE_CONNECTED_FAIL)
//        {
//            emit error(m_dbError,sql);
//            return;
//        }

//        qDebug()<<"wait for db connect...";
//        this->thread()->sleep(500);
//    }

    if(!sql->exec())
    {
        QSqlError err(sql->lastError());
        emit error(err,sql);
    }
    else
    {
        emit result(sql);
    }
}
