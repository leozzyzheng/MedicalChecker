#ifndef QUERYHELPER_H
#define QUERYHELPER_H

#include <QObject>

class QSqlQueryEx;
class QSqlError;

class QueryHelper : public QObject
{
    Q_OBJECT
public:
    explicit QueryHelper(QObject *parent = 0);
    void emitResult(QSqlQueryEx * pQuery);
    void emitError(QSqlError &error, QSqlQueryEx * pQuery);
signals:
    void result(QSqlQueryEx * pQuery);
    void error(QSqlError &error, QSqlQueryEx * pQuery);
};

#endif // QUERYHELPER_H
