import QtQuick 2.0

Image
{
    source:"qrc:/qml/Resource/stratup.jpg"
    opacity:1

    Connections {
        target : initProxy

        onCompleted:
        {
            rootStackView.push(Qt.resolvedUrl("Component/signature.qml"));
        }

        onError:
        {
            console.log(errorString);
            rootStackView.exit()
        }
    }

    Component.onCompleted:
    {
        initProxy.excuteInit();
    }
}
