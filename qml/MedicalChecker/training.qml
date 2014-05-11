import QtQuick 2.0
import "Component"

Rectangle {
    id:trainingPage
    width: parent.width
    height: parent.height

    property bool isBusy: false

    function changeDate()
    {

    }

    Component.onCompleted:
    {
        trainProxy.queryTraining(qmlHelper.getCurrDateTime("yyyy-MM-dd HH:mm:ss"));
        isBusy = true;
    }

    Connections
    {
        target:trainProxy

        onError:
        {
            console.log(errorString);
        }
    }

    TopBar
    {
        id:top
    }

    Rectangle
    {
        id:topicRect
        y:top.y + top.height
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

            Grid
            {
                columns: 2
                columnSpacing: 30
                rowSpacing: 10

                TimePicker
                {
                    id:picker

                    onDecDate:
                    {
                        changeDate();
                    }

                    onIncDate:
                    {
                        changeDate();
                    }
                }

                Rectangle
                {
                    id:placeHolder
                    width:1
                    height:1
                    color:"#00000000"
                }

                Rectangle
                {
                    width:320
                    height:550
                    border.width: 2
                    border.color: marco.backBlue

                    ListView
                    {
                        anchors.fill: parent
                        model:0
                        delegate:
                            TrainingTextNode{
                            index: index
                            titleText: "HIPPA"
                            timeText: trainProxy.getTrainingInfo(index,marco.trTime)
                            placeText: trainProxy.getTrainingInfo(index,marco.trAdd)
                            staffText: trainProxy.getTrainingInfo(index,marco.trStaff)

                            onClicked:
                            {
                                console.log(myIdx);
                            }
                        }
                    }
                }
            }
        }
    }
}
