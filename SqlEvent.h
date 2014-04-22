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
    void        result(QSqlQuery & result);
    void        error(QSqlError & error);

public slots:
    EventType type() const;

private:
    EventType m_type;

protected:
    SqlOperator * m_pSqlOp;
};

#endif // SQLEVENT_H