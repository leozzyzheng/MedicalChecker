#ifndef QSQLQUERYEX_H
#define QSQLQUERYEX_H

#include <QSqlQuery>
#include <QString>

class QSqlQueryEx : public QSqlQuery
{
public:
    explicit QSqlQueryEx(QSqlResult *r);
    explicit QSqlQueryEx(const QString& query = QString(), QSqlDatabase db = QSqlDatabase());
    explicit QSqlQueryEx(QSqlDatabase db);
    QSqlQueryEx(const QSqlQuery& other);

    void setID(QString &id);
    const QString & getID() const;
    void setID(QString id);

private:
    QString m_id;
};

#endif // QSQLQUERYEX_H
