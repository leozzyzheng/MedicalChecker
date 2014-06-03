#ifndef QSQLQUERYEX_H
#define QSQLQUERYEX_H

#include <QString>
#include <QMetaType>
#include <QDebug>
#include <vector>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtCore>
#include "Model/Marco.h"

#include "QueryHelper.h"
#include "QSqlRecordEx.h"
#include "QSqlErrorEx.h"

class QSqlQueryEx
{
public:
    explicit QSqlQueryEx(const QString& query = QString());
    QSqlQueryEx(const QSqlQueryEx & other);

    void setID(const QString &id);
    const QString & getID() const;

    QString getSqlString() const;
    void setSqlString(const QString & sql);

    void replaceHolder(const QString & holder, const QVariant & value);
    void threaBindValue(const QString & holder, const QVariant & value);

    void setExecutable(bool excutable);
    bool getExecutable() const;

    QueryHelper *getHelper();

    void emitResult();
    void emitError(QSqlErrorEx &error);

    bool exec();

    bool next();

    QSqlRecordEx record() const;
    QVariant value(int index);

    int size() const;
    int numRowsAffected() const;

    QSqlErrorEx error() const;

    bool isActive() const;
    int getCurrCount() const;
    QVector<QSqlRecordEx> getAllData() const;


private:
    struct PrepareData
    {
        QString holder;
        QVariant value;
    };

    QString m_id;
    QueryHelper m_helper;
    QString m_sql;
    bool m_bCanExecute;
    std::vector<PrepareData> m_vPre;
    QNetworkReply * m_pReply;
    QVector<QSqlRecordEx> m_vRecord;
    int m_currCount;
    int m_size;
    int m_numRowsAffected;
    QSqlErrorEx m_error;
    bool m_bActive;
};

Q_DECLARE_METATYPE(QSqlQueryEx)

#endif // QSQLQUERYEX_H
