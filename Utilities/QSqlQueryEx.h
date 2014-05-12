#ifndef QSQLQUERYEX_H
#define QSQLQUERYEX_H

#include <QSqlQuery>
#include <QString>
#include <QMetaType>
#include <QDebug>

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

    QString getSqlString() const;
    void setSqlString(const QString & sql);

    void replaceHolder(const QString & holder,const QVariant & value,bool isQuoted = false);

    void setExecutable(bool excutable);
    bool getExecutable() const;

    QueryHelper *getHelper();

    void emitResult();
    void emitError(QSqlError &error);

private:
    //disable perpare function for thread safe
    bool prepare(const QString &query){Q_UNUSED(query);return false;}

    QString m_id;
    QueryHelper m_helper;
    QString m_sql;
    bool m_bCanExecute;
};

Q_DECLARE_METATYPE(QSqlQueryEx)

#endif // QSQLQUERYEX_H
