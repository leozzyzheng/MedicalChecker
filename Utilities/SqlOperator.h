//负责mysql数据库操作的单例类,需要在程序开始时初始化
//数据库操作是在子线程进行的,
//exec提供两种query方法,需要链接result信号和error信号来获取结果

#ifndef SQLOPERATOR_H
#define SQLOPERATOR_H

#include <QObject>
#include <QThread>
#include <QtGui/QGuiApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>

#include "Utilities/ThreadSingleton.h"
#include "Utilities/QSqlQueryEx.h"
#include "Model/Marco.h"

//数据操作子线程类
class SqlThread : public QObject
{
    Q_OBJECT
public :
    SqlThread();
    ~SqlThread();
    void        moveToOtherThread();
    bool        isOpen();
    const QSqlError   getLastError();

public slots:
    void        exec(const QString & sql);
    void        exec(QSqlQueryEx sql);
    void        init();

signals:
    void        result(QSqlQueryEx result);
    void        error(QSqlError error);

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
    const QSqlError   getLastError();

signals:
    void        result(QSqlQueryEx result);
    void        error(QSqlError error);
    void        threadInit();

public slots:
    void        exec(QString & sql);
    void        exec(QSqlQueryEx sql);

signals:
    void        innerExec(const QString & sql);
    void        innerExec(QSqlQueryEx sql);

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
