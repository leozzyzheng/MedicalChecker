#include "ThreadSingleton.h"


QThread *ThreadSingleton::getInstance()
{
    return m_instance;
}
