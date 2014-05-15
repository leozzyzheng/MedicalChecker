import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:sterilzePage
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
        width: sterilzePage.width

        MyComponent.TopicBar
        {
            id:topicBar
            topic: "DISINFECT"
        }
    }

    Rectangle
    {
        id:background
        width:sterilzePage.width
        height:sterilzePage.height - top.height - topicBar.height
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
