#include "SqlOperator.h"

SqlOperator::~SqlOperator()
{
    m_pSqlThread->deleteLater();
}

void SqlOperator::Init()
{
    if(!m_pSqlThread)
    {
        delete m_pSqlThread;
    }

    m_pSqlThread = new SqlThread();

    connect(m_pSqlThread, SIGNAL(result(QSqlQuery&)),   this, SIGNAL(result(QSqlQuery&)));
    connect(m_pSqlThread, SIGNAL(error(QSqlError&)),    this, SIGNAL(error(QSqlError&)));

    m_pSqlThread->moveToOtherThread();
}

bool SqlOperator::isOpen()
{
    return m_pSqlThread->isOpen();
}

QSqlError SqlOperator::getLastError()
{
    return m_pSqlThread->getLastError();
}

SqlOperator::SqlOperator()
{
    m_pSqlThread = NULL;
}

void SqlOperator::exec(QString &sql)
{
    m_pSqlThread->exec(sql);
}

void SqlOperator::exec(QSqlQuery &sql)
{
    m_pSqlThread->exec(sql);
}


SqlThread::SqlThread()
{
    m_db = QSqlDatabase::addDatabase(DATABASE_TYPE);
    m_db.setHostName("localhost");
    m_db.setDatabaseName("world");
    m_db.setUserName("root");
    m_db.setPassword("6235775");

    if (!m_db.open())
    {
        qDebug()<<m_db.lastError().text();
        return;
    }
    else
    {
        qDebug()<<"Successful open database :" << m_db.databaseName() <<"!";
    }

    connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  this,       SLOT(deleteLater()));
}

SqlThread::~SqlThread()
{
    m_db.close();
}

void SqlThread::moveToOtherThread()
{
    m_pThread = new QThread();

    connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  m_pThread,  SLOT(quit()));
    connect(m_pThread,                      SIGNAL(finished()),     m_pThread,  SLOT(deleteLater()));

    moveToThread(m_pThread);
    m_pThread->start();
}

bool SqlThread::isOpen()
{
    return m_db.isOpen();
}

QSqlError SqlThread::getLastError()
{
    return m_db.lastError();
}

void SqlThread::exec(QString & sql)
{
    QSqlQuery query;

    if(!query.exec(sql))
    {
        QSqlError err = query.lastError();
        emit error(err);
    }
    else
    {
        emit result(query);
    }
}

void SqlThread::exec(QSqlQuery &sql)
{
    if(!sql.exec())
    {
        QSqlError err = sql.lastError();
        emit error(err);
    }
    else
    {
        emit result(sql);
    }
}
