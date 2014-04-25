#ifndef QSQLQUERYEX_H
#define QSQLQUERYEX_H

#include <QSqlQuery>
#include <QString>

class QSqlQueryEx : public QSqlQuery
{
public:
    explicit QSqlQueryEx();
    void setID(QString &id);
    const QString & getID() const;
    void setID(QString id);

private:
    QString m_id;
};

#endif // QSQLQUERYEX_H
