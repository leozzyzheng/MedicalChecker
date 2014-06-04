//负责mysql数据库操作的单例类,需要在程序开始时初始化
//数据库操作是在子线程进行的,
//exec提供两种query方法,需要链接result信号和error信号来获取结果

#ifndef SQLOPERATOR_H
#define SQLOPERATOR_H

#include <QObject>
#include <QThread>
#include <QtGui/QGuiApplication>
#include <QString>

#include "Utilities/ThreadSingleton.h"
#include "Utilities/QSqlQueryEx.h"
#include "Model/Marco.h"

class SqlOperator;

//数据操作子线程类
class SqlThread : public QObject
{
    Q_OBJECT
public :
    SqlThread();
    ~SqlThread();
    void        moveToOtherThread();
    bool        isOpen();

public slots:
    void        exec(QSqlQueryEx * sql);
    void        init(SqlOperator *self);

signals:
    void        innerresult(QSqlQueryEx * result);
    void        innererror(QSqlErrorEx error, QSqlQueryEx* sql);
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

signals:
    void        threadInit(SqlOperator * self);

public slots:
    void        exec(QSqlQueryEx * sql);
    void        result(QSqlQueryEx * result);
    void        error(QSqlErrorEx error, QSqlQueryEx *sql);

signals:
    void        innerExec(const QString & sql);
    void        innerExec(QSqlQueryEx * sql);

private:
    SqlThread * m_pSqlThread;
};


//单例类
class SqlSingleton
{
private:
    SqlSingleton(){}
    static SqlOperator * m_instance;

public:
    static SqlOperator * getInstance()
    {
        if(m_instance == NULL)
        {
            m_instance = new SqlOperator();
        }

        return m_instance;
    }
};

#endif // SQLOPERATOR_H
