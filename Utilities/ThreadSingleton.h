//逻辑线程使用的单例线程指针,所有逻辑线程都可以归入此线程

#ifndef THREADSINGLETON_H
#define THREADSINGLETON_H

#include <QThread>
#include <QDebug>

//单例类
class ThreadSingleton
{
private:
    static QThread* m_instance;
    ThreadSingleton(){}

public:
    static QThread* getInstance()
    {
        return m_instance;
    }
};

#endif // THREADSINGLETON_H
