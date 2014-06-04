#include "ThreadSingleton.h"


QThread *ThreadSingleton::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new QThread();
    }

    return m_instance;
}
