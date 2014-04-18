#include <QtGui/QGuiApplication>
#include "Utilities/SqlOperator.h"
#include "qtquick2applicationviewer.h"

//外部初始化单例
const QThread* ThreadSingleton::m_instance = new QThread();//逻辑单例线程
SqlOperator* SqlSingleton::m_instance = new SqlOperator;//多线程数据库封装单例

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //启动逻辑线程
    QThread * pLogicThread = ThreadSingleton::getInstance();
    connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  pLogicThread,  SLOT(quit()));
    connect(pLogicThread,                   SIGNAL(finished()),     pLogicThread,  SLOT(deleteLater()));
    pLogicThread->start();

    //初始化数据库连接
    SqlSingleton::getInstance()->Init();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/MedicalChecker/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
