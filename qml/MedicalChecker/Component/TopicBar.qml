import QtQuick 2.0

Rectangle {
    property string topic: "Topic"

    width: parent.width
    height: 44
    
    Row
    {
        Image
        {
            width:42
            height:43
            source:"qrc:/qml/Resource/arrow-left-topic.png"

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    rootStackView.pop();
                }
            }
        }
        
        Rectangle
        {
            height:44
            width:parent.width

            Text
            {
                text:topic
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "verdana,Lucida Sans,trebuchet ms,arial,sans-serif"
            }
        }

    }
}
