#include <QtGui/QGuiApplication>
#include <QtQml>

#include "qtquick2applicationviewer.h"

#include "Utilities/SqlOperator.h"
#include "Utilities/SignatureSender.h"
#include "Signature.h"

//外部初始化单例
QThread* ThreadSingleton::m_instance = new QThread();//逻辑单例线程
SqlOperator* SqlSingleton::m_instance = new SqlOperator;//多线程数据库封装单例

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Signature>("com.zzy.qmlcomponents", 1, 0, "Signature");

    //启动逻辑线程
    QThread * pLogicThread = ThreadSingleton::getInstance();
    QObject::connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  pLogicThread,  SLOT(quit()));
    QObject::connect(pLogicThread,                   SIGNAL(finished()),     pLogicThread,  SLOT(deleteLater()));
    pLogicThread->start();

    //初始化数据库连接
    SqlSingleton::getInstance()->Init();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/MedicalChecker/main.qml"));
    viewer.showExpanded();

    QImage image("D:/GitHub/MedicalChecker/trunk/test.png");
    SignatureSender sender;
    sender.sendSigature(image);

    return app.exec();
}
