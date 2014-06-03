#ifndef QUERYHELPER_H
#define QUERYHELPER_H

#include <QObject>

class QSqlQueryEx;
class QSqlErrorEx;

class QueryHelper : public QObject
{
    Q_OBJECT
public:
    explicit QueryHelper(QObject *parent = 0);
    void emitResult(QSqlQueryEx * pQuery);
    void emitError(QSqlErrorEx &error, QSqlQueryEx * pQuery);
signals:
    void result(QSqlQueryEx * pQuery);
    void error(QSqlErrorEx &error, QSqlQueryEx * pQuery);
};

#endif // QUERYHELPER_H
