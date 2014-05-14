import QtQuick 2.0
import "Component"

Rectangle {
    id:trainingPage
    width: parent.width
    height: parent.height

    property bool isBusy: false

    function changeDate()
    {
        trainProxy.abort();
        trainProxy.queryTraining(qmlHelper.getCurrDateTime("yyyy-MM-dd"));
    }

    Component.onCompleted:
    {
        trainProxy.queryTraining(qmlHelper.getCurrDateTime("yyyy-MM-dd"));
        isBusy = true;
    }

    Connections
    {
        target:trainProxy

        onError:
        {
            console.log(errorString);
        }

        onTrainingInfoStandBy:
        {
            trainingList.model = 0;
            trainingList.model = trainProxy.getTrainingNum();
        }

        onStaffInfoStandBy:
        {
            nameList.model = 0;
            nameList.model = trainProxy.getStaffNum();
            nameList.height = nameList.contentHeight > 480 ? 480 : nameList.contentHeight;
        }

        onClear:
        {
            trainingList.model = 0;
            nameList.model = 0;
            nameText.text = "click me to choose your name";
            signer.clearImage();
        }

        onClearSignInfo:
        {
            nameList.model = 0;
            nameText.text = "click me to choose your name";
            signer.clearImage();
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
                    clip:true

                    ListView
                    {
                        id:trainingList
                        width:parent.width - parent.border.width*2
                        height:parent.height - parent.border.width*2
                        anchors.centerIn: parent
                        model:trainProxy.getTrainingNum()

                        delegate:
                            TrainingTextNode{
                            innerIdx: index
                            titleText: trainProxy.getTrainingInfo(index,marco.trType)
                            timeText: trainProxy.getTrainingInfo(index,marco.trTime)
                            placeText: trainProxy.getTrainingInfo(index,marco.trAdd)
                            staffText: trainProxy.getTrainingInfo(index,marco.trStaff)

                            onNodeClicked:
                            {
                                trainProxy.queryTrainingStaff(trainProxy.getTrainingInfo(index,marco.trTrid));
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
                            z:10

                            Text
                            {
                                id:nameText
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
                                    nameListRect.visible = true;
                                }
                            }

                            Rectangle
                            {
                                id:nameListRect
                                width:nameList.width
                                height:nameList.height
                                visible:false
                                clip:true

                                NameList
                                {
                                    id:nameList
                                    onNodeClicked:
                                    {
                                        nameText.text = name;
                                        nameListRect.visible = false;
                                    }
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
                                                if(nameText.text == "click me to choose your name")
                                                    return;

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
