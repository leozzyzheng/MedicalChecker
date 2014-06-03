#ifndef QSQLRECORDEX_H
#define QSQLRECORDEX_H

#include <QVector>
#include <QMap>
#include <QString>
#include <QVariant>

class QSqlRecordEx
{
public:
    QSqlRecordEx();
    QSqlRecordEx(const QSqlRecordEx & other) ;

    void push(const QVariantMap &map);
    int indexOf(const QString & key);
    QVariant value(int index) const;
    QString key(int index) const;
    int size() const;
private:
    QVector<QVariant> m_data;
    QVector<QString> m_keys;
};

#endif // QSQLRECORDEX_H
