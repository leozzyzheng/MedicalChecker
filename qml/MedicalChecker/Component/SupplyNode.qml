import QtQuick 2.0

Rectangle {
    id:iconRect
    width: 150
    height: 130

    property string iconText: ""

    signal nodeClicked();

    Column
    {
        Image
        {
            id:pic
            y:20
            anchors.horizontalCenter: iconRect.horizontalCenter
            source:"qrc:/qml/Resource/iOS7_-icons__01_03.png"
        }

        Rectangle
        {
            width:iconRect.width
            height:iconRect.height - pic.height

            Text
            {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.family: marco.topicFontFa
                color:marco.fontBlue
                font.pixelSize: marco.suppFontpSize
                text:iconText
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            nodeClickde();
        }
    }
}
