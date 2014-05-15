import QtQuick 2.0

Rectangle {
    id:component
    width: 450
    height: 100
    color: backColor

    property string innerText: "Clean Item"
    property string backColor: "#FFFFFF"
    property string imgSrc: ""

    signal nodeClicked()

    function select()
    {
        nodeText.color = marco.fontWhite;
        nodeText.font.weight = Font.bold;
        selectRect.color = marco.backBlue;
    }

    function clearSelection()
    {
        nodeText.color = marco.fontBlue;
        nodeText.font.weight = Font.Normal;
        selectRect.color = "#00000000";
    }

    Rectangle
    {
        id: selectRect
        width: component.width - 16
        height: component.height - 8
        anchors.centerIn: parent
        color:"#00000000"

        Row
        {
            Rectangle
            {
                id:textBox
                width:selectRect.width - doneIcon.width
                height:selectRect.height
                color:"#00000000"

                Text
                {
                    id:nodeText
                    anchors.centerIn: parent
                    font.family: marco.topicFontFa
                    font.pixelSize: marco.dCleanFontpSize
                    color : marco.fontBlue
                    text : innerText
                    font.weight : Font.Normal
                }
            }

            Rectangle
            {
                id:doneIcon
                width:100
                height:selectRect.height
                color:"#00000000"

                Image
                {
                    anchors.centerIn: parent
                    source:imgSrc
                }
            }
        }
    }

    Rectangle
    {
        height:1
        width:parent.width
        border.width: 1
        border.color: marco.borderColor
    }


    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            nodeClicked();
        }

        onReleased:
        {
            clearSelection();
        }

        onPressed:
        {
            select();
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
