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

                Rectangle
                {
                    width:600
                    height:550
                    color:"#00000000"

                    Column
                    {
                        spacing: 30

                        Rectangle
                        {
                            id:namechooser
                            width:600
                            height:30

                            Text
                            {
                                id:nameText
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                anchors.fill: parent
                                text:"click me to choose your name"
                                font.family: marco.topicFontFa
                            }

                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    nameList.visible = true;
                                }
                            }

                            NameList
                            {
                                id:nameList
                                visible:false

                                onClicked:
                                {
                                    nameText.text = name;
                                    visible = false;
                                }
                            }
                        }

                        Signature
                        {
                            id:signer
                            width:600
                            height:485

                            Rectangle
                            {
                                anchors.bottom: parent.bottom
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                anchors.bottomMargin: 10
                                width:185
                                height:30

                                Row
                                {
                                    spacing: 25
                                    Image
                                    {
                                        id:resetBtn
                                        source:"qrc:/qml/Resource/btn-reset.png"

                                        MouseArea
                                        {
                                            anchors.fill: parent

                                            onClicked:
                                            {
                                                signer.clearImage();
                                            }

                                            onPressed:
                                            {
                                                resetBtn.source = "qrc:/qml/Resource/btn-reset-click.png"
                                            }

                                            onReleased:
                                            {
                                                resetBtn.source = "qrc:/qml/Resource/btn-reset.png"
                                            }

                                            onExited:
                                            {
                                                resetBtn.source = "qrc:/qml/Resource/btn-reset.png"
                                            }
                                        }
                                    }

                                    Image
                                    {
                                        id:okBtn
                                        source:"qrc:/qml/Resource/btn-ok.png"

                                        MouseArea
                                        {
                                            anchors.fill: parent

                                            onClicked:
                                            {
                                                signer.sendImage(nameText.text);
                                            }

                                            onPressed:
                                            {
                                                okBtn.source = "qrc:/qml/Resource/btn-ok-click.png"
                                            }

                                            onReleased:
                                            {
                                                okBtn.source = "qrc:/qml/Resource/btn-ok.png"
                                            }

                                            onExited:
                                            {
                                                okBtn.source = "qrc:/qml/Resource/btn-ok.png"
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
