//负责mysql数据库操作的单例类,需要在程序开始时初始化
//数据库操作是在子线程进行的,
//exec提供两种query方法,需要链接result信号和error信号来获取结果

#ifndef SQLOPERATOR_H
#define SQLOPERATOR_H

#include <QObject>
#include <QThread>
#include <QtGui/QGuiApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "Utilities/ThreadSingleton.h"

#define DATABASE_TYPE "QMYSQL"

//数据操作子线程类
class SqlThread : public QObject
{
    Q_OBJECT
public :
    SqlThread();
    ~SqlThread();
    void        moveToOtherThread();
    bool        isOpen();
    QSqlError   getLastError();

public slots:
    void        exec(QString & sql);
    void        exec(QSqlQuery & sql);

signals:
    void        result(QSqlQuery & result);
    void        error(QSqlError & error);

private:
    QSqlDatabase    m_db;
};

//数据库操作主线程封装类
class SqlOperator : public QObject
{
    Q_OBJECT
public :
    SqlOperator();
    ~           SqlOperator();
    void        Init();
    bool        isOpen();
    QSqlError   getLastError();

signals:
    void        result(QSqlQuery & result);
    void        error(QSqlError & error);

public slots:
    void        exec(QString & sql);
    void        exec(QSqlQuery & sql);

private:
    SqlThread * m_pSqlThread;
};


//单例类
class SqlSingleton
{
private:
    static SqlOperator* m_instance;
    SqlSingleton(){}

public:
    static SqlOperator* getInstance()
    {
        return m_instance;
    }
};

#endif // SQLOPERATOR_H
