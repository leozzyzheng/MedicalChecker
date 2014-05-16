import QtQuick 2.0

Rectangle {
    property string topic: "Topic"

    id:topicRect
    width: parent.width
    height: 44

    signal poped()
    
    Rectangle
    {
        height:44
        width:topicRect.width

        Text
        {
            anchors.fill: parent
            text:topic
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: marco.topicFontFa
            color:marco.fontBlue
            font.pixelSize: marco.topicFontpSize
        }
    }

    Image
    {
        x:0
        id:backIcon
        width:42
        height:43
        source:"qrc:/qml/Resource/arrow-left-topic.png"

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                poped();
                rootStackView.pop();
                console.log("pop");
            }
        }
    }
}
