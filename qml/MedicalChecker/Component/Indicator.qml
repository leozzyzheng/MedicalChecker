import QtQuick 2.0

ListView {
    property int maxHeight: 0

    id:list

    signal clickedIndicator(string originName)

    model: initProxy.getInfoNum();
    delegate:
        Rectangle{

        Component.onCompleted:
        {
            list.height += height;

            if(list.height > maxHeight)
                list.height = maxHeight;
        }

        width:parent.width
        height: innerText.height + 10
        border.color: "red"
        border.width: 1
        radius: 5

        Text
        {
            x:20
            y:5
            id : innerText
            width:parent.width
            verticalAlignment: Text.Center
            wrapMode: Text.Wrap
            elide: Text.ElideRight
            text:initProxy.getShownName(index)
        }

        MouseArea
        {
            anchors.fill: parent
            onCanceled:
            {
//                selected="#ffffff";
//                textC="#000000";
                console.log("cancel");
            }
            onReleased:
            {
//                selected="#ffffff";
//                textC="#000000";
                console.log("released");
            }
            onPressed:
            {
                console.log("press");
//                selected="#282828";
//                textC="#ffffff";
            }
            onClicked:
            {
                console.log("click");
                clickedIndicator(initProxy.getOriginName(index))
            }

        }
    }
}
