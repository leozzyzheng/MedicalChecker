import QtQuick 2.0

Rectangle {

    property int innerIdx: 0
    property string titleText: "HIPPA"
    property string timeText: "TIME : 06:00PM"
    property string placeText: "PLACE : ROOM1"
    property string staffText: "WHO : GangGe"
    property string titleColor: marco.fontBlack
    property string backColor: marco.backGray
    property string innerFontColor: marco.fontBlack

    signal nodeClicked()

    function select()
    {
        componentRoot.border.width = 1;
        componentRoot.border.color = marco.backBlue;
        titleColor = marco.fontBlue;
        backColor = marco.backBlue;
        innerFontColor = marco.fontWhite;
    }

    function clearSelection()
    {
        componentRoot.border.width = 0;
        titleColor = marco.fontBlack;
        backColor = marco.backGray;
        innerFontColor = marco.fontBlack;
    }

    id:componentRoot
    width: parent.width
    height: 150

    Column
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
                    text:innerIdx + "." + titleText
                    font.family: marco.topicFontFa
                    verticalAlignment: Text.AlignVCenter
                    color: titleColor
                }
            }
        }

        Rectangle
        {
            id:contentRect
            x:2
            width:componentRoot.width - 4
            height:componentRoot.height - title.height - 2
            color:backColor

            Column
            {
                TrainingTextInnerContentNode
                {
                    id:timeContent
                    width: contentRect.width
                    contentText: timeText
                    innerColor: backColor
                    fontColor:innerFontColor
                }

                TrainingTextInnerContentNode
                {
                    id:placeContent
                    width: contentRect.width
                    contentText: placeText
                    innerColor: backColor
                    fontColor:innerFontColor
                }

                TrainingTextInnerContentNode
                {
                    id:staffContent
                    width: contentRect.width
                    contentText: staffText
                    innerColor: backColor
                    fontColor:innerFontColor
                }
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            nodeClicked();
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

        onCanceled:
        {
            clearSelection();
        }
    }

}
