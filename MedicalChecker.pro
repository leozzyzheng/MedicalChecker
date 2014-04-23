# Add more folders to ship with the application, here
folder_01.source = qml/MedicalChecker
folder_01.target = qml

DEPLOYMENTFOLDERS = folder_01

QT += sql qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    Utilities/SqlOperator.cpp \
    Utilities/SignatureSender.cpp \
    Signature.cpp \
    SqlEvent.cpp \
    Model/LoginInfo.cpp \
    InitProxy.cpp

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
    InitProxy.h

OTHER_FILES += \
    qml/MedicalChecker/startup.qml \
    qml/MedicalChecker/Component/Indicator.qml \
    qml/MedicalChecker/Component/Signature.qml

RESOURCES += \
    Resource.qrc
