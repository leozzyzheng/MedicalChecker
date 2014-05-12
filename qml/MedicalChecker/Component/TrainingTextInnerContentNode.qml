import QtQuick 2.0

Rectangle {
    property string contentText: "06:00PM"
    property string fontColor: marco.fontBlack
    property string innerColor: marco.backGray

    id:content
    height:25
    color: innerColor

    Rectangle
    {
        x:20
        width:parent.width - x
        height:parent.height
        color: innerColor

        Text
        {
            anchors.fill: parent
            text:contentText
            font.family: marco.topicFontFa
            verticalAlignment: Text.AlignVCenter
            color:fontColor
        }
    }
}
