import QtQuick 2.0

Rectangle {
    property string contentText: "06:00PM"
    property string fontColor: marco.fontBlack

    id:content
    height:25

    Rectangle
    {
        x:20
        width:parent.width - x
        height:parent.height

        Text
        {
            anchors.fill: parent
            text:contentText
            font.family: marco.topicFontFa
            verticalAlignment: Text.AlignVCenter
            color:marco.fontBlack
        }
    }
}
