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

    connect(m_pSqlThread, SIGNAL(result(QSqlQueryEx)),              this, SIGNAL(result(QSqlQueryEx)));
    connect(m_pSqlThread, SIGNAL(error(const QSqlError&)),          this, SIGNAL(error(const QSqlError&)));
    connect(this,         SIGNAL(innerExec(const QString &)),       m_pSqlThread, SLOT(exec(const QString &)));
    connect(this,         SIGNAL(innerExec(QSqlQueryEx)),           m_pSqlThread, SLOT(exec(QSqlQueryEx)), Qt::QueuedConnection);
    connect(this,         SIGNAL(threadInit()),                     m_pSqlThread, SLOT(init()), Qt::QueuedConnection);

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

void SqlOperator::exec(QString &sql)
{
    emit innerExec(sql);
}

void SqlOperator::exec(QSqlQueryEx sql)
{
    emit innerExec(sql);
}


SqlThread::SqlThread()
{
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

void SqlThread::exec(const QString & sql)
{
    QSqlQueryEx query;

    if(!query.exec(sql))
    {
        const QSqlError err = query.lastError();
        emit error(err);
    }
    else
    {
        emit result(query);
    }
}

void SqlThread::exec(QSqlQueryEx sql)
{
    if(!sql.exec())
    {
        const QSqlError err = sql.lastError();
        emit error(err);
    }
    else
    {
        emit result(sql);
    }
}
