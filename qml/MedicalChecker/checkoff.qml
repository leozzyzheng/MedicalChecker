import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:checkPage
    width: parent.width
    height: parent.height

    property bool isBusy: false

    MyComponent.TopBar
    {
        id:top
    }

    Rectangle
    {
        id:topicRect
        y:top.y + top.height
        height: topicBar.height
        width: checkPage.width

        MyComponent.TopicBar
        {
            id:topicBar
            topic: "CHECK-OFF"
        }
    }

    Rectangle
    {
        id:background
        width:checkPage.width
        height:checkPage.height - top.height - topicBar.height
        y:topicRect.y + topicRect.height

        Image
        {
            anchors.fill: parent
            fillMode: Image.Tile
            source:"qrc:/qml/Resource/background.png"
        }

        Rectangle
        {
            id:content
            width:950
            height:610
            y:10
            anchors.horizontalCenter: parent.horizontalCenter
            color:"#00000000"
        }
    }
}
