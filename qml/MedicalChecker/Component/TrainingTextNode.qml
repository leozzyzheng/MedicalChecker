import QtQuick 2.0

Rectangle {

    property int index: 0
    property string titleText: "HIPPA"
    property string timeText: "TIME : 06:00PM"
    property string placeText: "PLACE : ROOM1"
    property string staffText: "WHO : GangGe"
    property string titleColor: marco.fontBlue
    property string backBlue: marco.backGray

    signal clicked(int myIdx)

    function select()
    {
        componentRoot.border.width = 1;
        componentRoot.border.color = marco.backBlue;
        titleColor = marco.fontBlue;
        backBlue = marco.backBlue;
        timeContent.fontColor = marco.fontWhite;
        placeContent.fontColor = marco.fontWhite;
        staffContent.fontColor = marco.fontWhite;
    }

    function clearSelection()
    {
        componentRoot.border.width = 0;
        titleColor = marco.fontBlack;
        backBlue = marco.backGray;
        timeContent.fontColor = marco.fontBlack;
        placeContent.fontColor = marco.fontBlack;
        staffContent.fontColor = marco.fontBlack;
    }

    id:componentRoot
    width: 320
    height: 150

    Row
    {
        Rectangle
        {
            id:title
            width:componentRoot.width
            height:55

            Rectangle
            {
                x:12
                width:parent.width - x
                height:parent.height

                Text
                {
                    anchors.fill: parent
                    text:index + "." + titleText
                    font.family: marco.topicFontFa
                    verticalAlignment: Text.AlignVCenter
                    color: titleColor
                }
            }
        }

        Rectangle
        {
            id:contentRect
            x:1
            width:componentRoot.width-2
            height:componentRoot.height - title.height - 1
            color:backBlue

            Row
            {
                TrainingTextInnerContentNode
                {
                    id:timeContent
                    width: contentRect.width
                    contentText: timeText
                }

                TrainingTextInnerContentNode
                {
                    id:placeContent
                    width: contentRect.width
                    contentText: placeText
                }

                TrainingTextInnerContentNode
                {
                    id:staffContent
                    width: contentRect.width
                    contentText: staffText
                }
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            clicked(index);
        }

        onPressed:
        {
            select();
        }

        onReleased:
        {
            clearSelection();
        }

        onExited:
        {
            clearSelection();
        }
    }

}
