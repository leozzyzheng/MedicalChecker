#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#include <QObject>
#include <QCoreApplication>
#include <QString>
#include <QSettings>
#include <QDebug>

class GlobalHelper : public QObject
{
    Q_OBJECT
public:
    explicit GlobalHelper(QObject *parent = 0);
    static void getUserAndPw(QString& username, QString & passwd);
    static void setUserAndPw(const QString& username, const QString & passwd);
    static void setGlobalValue(const QString & name, const QString & value);
    static QString getGlobalValue(const QString & name);
    static void clearGloabalValue(const QString & name);
signals:

public slots:

};

#endif // GLOBALHELPER_H
