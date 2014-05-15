import QtQuick 2.0
import "Component" as MyComponent


Rectangle {
    width: parent.width;
    height: parent.height;

    MyComponent.TopBar
    {
        id:top
    }

    MyComponent.TopicBar
    {
        id:topicBar
        y:top.y + top.height
        topic: "Home"
    }

    Rectangle
    {
        y:topicBar.y + topicBar.height
        width:parent.width
        height:parent.height - top.height - topicBar.height

        Image
        {
            anchors.fill: parent
            source:"qrc:/qml/Resource/background.png"
            fillMode:Image.Tile
        }

        Rectangle
        {
            width:570
            height:480
            color:"#00000000"

            anchors.horizontalCenter: parent.horizontalCenter
            y:0.382 * (parent.height -height)

            Grid
            {
                columns:2
                columnSpacing : 170
                rowSpacing: 80

                MyComponent.IndexComponent
                {
                    iconSrc: "qrc:/qml/Resource/icon-training.png"
                    iconClickSrc: "qrc:/qml/Resource/icon-training-click.png"
                    qmlSrc: "training.qml"
                    labelText: "TRAINING"
                }

                MyComponent.IndexComponent
                {
                    iconSrc: "qrc:/qml/Resource/icon-CHECK.png"
                    iconClickSrc: "qrc:/qml/Resource/icon-CHECK-click.png"
                    qmlSrc: "checkoff.qml"
                    labelText: "CHECK-OFF"
                }

                MyComponent.IndexComponent
                {
                    iconSrc: "qrc:/qml/Resource/icon-xiaodu.png"
                    iconClickSrc: "qrc:/qml/Resource/icon-xiaodu-click.png"
                    qmlSrc: "sterilization.qml"
                    labelText: "DISINFECT"
                }

                MyComponent.IndexComponent
                {
                    iconSrc: "qrc:/qml/Resource/icon-clean.png"
                    iconClickSrc: "qrc:/qml/Resource/icon-clean-click.png"
                    qmlSrc: "cleaning.qml"
                    labelText: "CLEAN"
                }
            }
        }
    }


}
