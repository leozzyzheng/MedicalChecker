#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#include <QObject>
#include <QCoreApplication>
#include <QString>
#include <QSettings>

class GlobalHelper : public QObject
{
    Q_OBJECT
public:
    explicit GlobalHelper(QObject *parent = 0);
    static void getUserAndPw(QString& username, QString & passwd);
    static void setUserAndPw(QString& username, QString & passwd);
    static void setGlobalValue(QString & name, QString & value);
    static QString getGlobalValue(QString & name);
signals:

public slots:

};

#endif // GLOBALHELPER_H
