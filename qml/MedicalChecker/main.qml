import QtQuick 2.0
import com.zzy.qmlcomponents 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Signature
    {
        width:50
        height:50
    }
}
