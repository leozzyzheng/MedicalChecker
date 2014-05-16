import QtQuick 2.0

Rectangle {
    id:component
    width: 450
    height: 100
    color: backColor

    property string innerText: "Clean Item"
    property string backColor: "#FFFFFF"
    property string imgSrc: "qrc:/qml/Resource/done.png"
    property bool canClicked: true
    property bool haveIcon: true
    property string unvisibleId: ""
    property bool isSelected: false

    signal nodeClicked()

    onIsSelectedChanged:
    {
        if(isSelected)
        {
            select();
        }
        else
        {
            clearSelection();
        }
    }

    function select()
    {
        nodeText.color = marco.fontWhite;
        nodeText.font.bold = true;
        selectRect.color = marco.backBlue;
    }

    function clearSelection()
    {
        if(isSelected)
            return;

        nodeText.color = marco.fontBlue;
        nodeText.font.bold = false;
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
                }
            }

            Rectangle
            {
                id:doneIcon
                width:haveIcon ? 100 : 0
                height:selectRect.height
                color:"#00000000"

                Image
                {
                    scale:0.8
                    anchors.centerIn: parent
                    source:haveIcon ? imgSrc : ""
                }
            }
        }
    }

    Rectangle
    {
        anchors.bottom: component.bottom
        height:2
        width:component.width
        border.width: 1
        border.color: marco.borderColor
    }


    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            if(canClicked)
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
