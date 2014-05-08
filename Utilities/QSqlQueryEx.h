#ifndef QSQLQUERYEX_H
#define QSQLQUERYEX_H

#include <QSqlQuery>
#include <QString>
#include <QMetaType>

#include "QueryHelper.h"

class QSqlQueryEx : public QSqlQuery
{
public:
    explicit QSqlQueryEx(QSqlResult *r);
    explicit QSqlQueryEx(const QString& query = QString(), QSqlDatabase db = QSqlDatabase());
    explicit QSqlQueryEx(QSqlDatabase db);
    QSqlQueryEx(const QSqlQueryEx & other);

    void setID(const QString &id);
    const QString & getID() const;

    QueryHelper *getHelper();

    void emitResult();
    void emitError(QSqlError &error);

private:
    QString m_id;
    QueryHelper m_helper;
};

Q_DECLARE_METATYPE(QSqlQueryEx)

#endif // QSQLQUERYEX_H
