#include <QtGui/QGuiApplication>
#include <QtQml>

#include "qtquick2applicationviewer.h"

#include "Utilities/SqlOperator.h"
#include "Utilities/SignatureSender.h"
#include "Utilities/QmlHelper.h"
#include "Model/Marco.h"
#include "Signature.h"
#include "InitProxy.h"
#include "TrainingProxy.h"

//外部初始化单例
QThread* ThreadSingleton::m_instance = new QThread();//逻辑单例线程
SqlOperator* SqlSingleton::m_instance = new SqlOperator;//多线程数据库封装单例

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    qRegisterMetaType<QSqlQueryEx>("QSqlQueryEx");
    qRegisterMetaType<QSqlError>("QSqlError");

    //注册自定义qml组件------------------------------------------------------
    qmlRegisterType<Signature>("com.zzy.qmlcomponents", 1, 0, "Signature");

    //----------------------------------------------------------------------


    //注册需要暴露给qml的类--------------------------------------------------

    //实例化类
    InitProxy initProxy;
    TrainingProxy trainProxy;
    QmlHelper qmlHelper;
    QmlMarco marco;

    //注册
    viewer.rootContext()->setContextProperty("initProxy", &initProxy);
    viewer.rootContext()->setContextProperty("trainProxy", &trainProxy);
    viewer.rootContext()->setContextProperty("qmlHelper", &qmlHelper);
    viewer.rootContext()->setContextProperty("marco", &marco);

    //---------------------------------------------------------------------



    //启动逻辑线程----------------------------------------------------------
    QThread * pLogicThread = ThreadSingleton::getInstance();
    QObject::connect(QGuiApplication::instance(),    SIGNAL(aboutToQuit()),  pLogicThread,  SLOT(quit()));
    QObject::connect(pLogicThread,                   SIGNAL(finished()),     pLogicThread,  SLOT(deleteLater()));
    pLogicThread->start();
    //---------------------------------------------------------------------



    //初始化数据库连接------------------------------------------------------
    SqlSingleton::getInstance()->Init();
    //---------------------------------------------------------------------

    viewer.setSource(QStringLiteral("qml/MedicalChecker/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
