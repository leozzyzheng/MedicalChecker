# Add more folders to ship with the application, here
folder_01.source = qml/MedicalChecker
folder_01.target = qml

DEPLOYMENTFOLDERS = folder_01

QT += qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Utilities/SqlOperator.cpp \
    Utilities/SignatureSender.cpp \
    Signature.cpp \
    SqlEvent.cpp \
    Model/LoginInfo.cpp \
    InitProxy.cpp \
    TrainingProxy.cpp \
    Model/TrainingInfo.cpp \
    Utilities/QSqlQueryEx.cpp \
    Utilities/QmlHelper.cpp \
    Utilities/GlobalHelper.cpp \
    Utilities/QueryHelper.cpp \
    Model/CleanInfo.cpp \
    DailyCleanProxy.cpp \
    WeeklyCleanProxy.cpp \
    SupplyProxy.cpp \
    CheckProxy.cpp \
    Model/CheckInfo.cpp \
    UserProxy.cpp \
    Model/UserInfo.cpp \
    InventoryProxy.cpp \
    Model/Inventory.cpp \
    SterilizeProxy.cpp \
    Model/SterilizeInfo.cpp \
    Utilities/QSqlErrorEx.cpp \
    Utilities/QSqlRecordEx.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    Utilities/SqlOperator.h \
    Utilities/ThreadSingleton.h \
    Utilities/SignatureSender.h \
    Signature.h \
    SqlEvent.h \
    Model/LoginInfo.h \
    InitProxy.h \
    TrainingProxy.h \
    Model/TrainingInfo.h \
    Utilities/QSqlQueryEx.h \
    Utilities/QmlHelper.h \
    Model/Marco.h \
    Utilities/GlobalHelper.h \
    Utilities/QueryHelper.h \
    Model/CleanInfo.h \
    DailyCleanProxy.h \
    WeeklyCleanProxy.h \
    SupplyProxy.h \
    CheckProxy.h \
    Model/CheckInfo.h \
    UserProxy.h \
    Model/UserInfo.h \
    InventoryProxy.h \
    Model/Inventory.h \
    SterilizeProxy.h \
    Model/SterilizeInfo.h \
    Utilities/QSqlErrorEx.h \
    Utilities/QSqlRecordEx.h

OTHER_FILES += \
    qml/MedicalChecker/startup.qml \
    qml/MedicalChecker/Component/Indicator.qml \
    qml/MedicalChecker/Component/Signature.qml \
    qml/MedicalChecker/training.qml \
    qml/MedicalChecker/Component/CleanTextNode.qml \
    qml/MedicalChecker/singleSig.qml

RESOURCES += \
    Resource.qrc
