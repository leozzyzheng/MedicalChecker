#ifndef QSQLERROREX_H
#define QSQLERROREX_H

#include <QString>
//#include <QMetaType>

class QSqlErrorEx
{
public:
    QSqlErrorEx(QString error = QString());
    QSqlErrorEx(const QSqlErrorEx & other);

    QString text() const;
    void setText(const QString &text) ;

private:
    QString m_txt;
};

//Q_DECLARE_METATYPE(QSqlErrorEx)

#endif // QSQLERROREX_H
