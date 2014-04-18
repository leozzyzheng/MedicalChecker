#include <QtGui/QGuiApplication>
#include "Utilities/SqlOperator.h"
#include "qtquick2applicationviewer.h"

//外部初始化单例
SqlOperator* SqlSingleton::m_instance = new SqlOperator;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //初始化数据库连接
    SqlSingleton::getInstance()->Init();

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/MedicalChecker/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
