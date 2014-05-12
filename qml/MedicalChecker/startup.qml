import QtQuick 2.0

Rectangle
{
    width:parent.width
    height:parent.height

    Image
    {
        anchors.centerIn: parent
        source:"qrc:/qml/Resource/starting page.png"
    }

    Connections {
        target : initProxy

        onCompleted:
        {
            console.log("Successfully get clinicNames");
            rootStackView.push({item:Qt.resolvedUrl("login.qml"),replace:true,destroyOnPop:true});
        }

        onError:
        {
            console.log(errorString);
            rootStackView.exit()
        }
    }
}
