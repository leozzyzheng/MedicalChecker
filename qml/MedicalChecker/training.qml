import QtQuick 2.0
import "Component"

Rectangle {
    id:trainingPage
    width: parent.width
    height: parent.height

    Component.onCompleted:
    {
        trainProxy.queryTraining();
    }

    Connections
    {
        target:trainProxy

        onError:
        {
            console.log(errorString);
        }
    }

    Row
    {
        TopBar
        {
            id:top
        }

        Rectangle
        {
            height: topicBar.height
            width: trainingPage.width

            TopicBar
            {
                id:topicBar
                topic: "TRAINING"
            }
        }

        Rectangle
        {
            id:background
            width:trainingPage.width
            height:trainingPage.height - top.height - topicBar.height

            Component.onCompleted:
            {
                console.log(width + " " + height + " " + y)
            }

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

                Grid
                {
                    columns: 2
                    columnSpacing: 30
                    rowSpacing: 5

                    TimePicker
                    {
                        id:picker

                        onDecDate:
                        {

                        }

                        onIncDate:
                        {

                        }
                    }

                    Rectangle
                    {
                        color:"#00000000"
                    }


                }
            }
        }
    }


}
