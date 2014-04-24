//所有数据库操作事件的基类

#ifndef SQLEVENT_H
#define SQLEVENT_H

#include <QObject>
#include "Utilities/SqlOperator.h"

class SqlEvent : public QObject
{
    Q_OBJECT
public:
    enum EventType
    {
        CLEAN_CHECK,
        TRANING_CHECK,
        NONE
    };

    explicit SqlEvent(QObject *parent = 0);

signals:
    void        originResult(QSqlQuery & result);
    void        priginError(QSqlError & error);

    void        error(QString errorString);
    void        completed();

public slots:
    EventType type() const;

    //提供两个可以被重写的槽函数来自定义sql查询后的操作
protected slots:
    virtual void innerError(QSqlError& error);
    virtual void innerFinished(QSqlQuery & query);

private:
    EventType m_type;

protected:
    SqlOperator * m_pSqlOp;
};

#endif // SQLEVENT_H
