import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:trainingPage
    width: parent.width
    height: parent.height

    property bool isBusy: false
    property string trId: ""
    property string staffId: ""

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
            rootStackView.showMsg(errorString);
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

        onUpdateSucc:
        {
            trainProxy.queryTraining(qmlHelper.getCurrDateTime("yyyy-MM-dd"));
            rootStackView.showMsg("Successfully Sign");
        }
    }

    MyComponent.TopBar
    {
        id:top
    }

    Rectangle
    {
        id:topicRect
        y:top.y + top.height
        height: topicBar.height
        width: trainingPage.width

        MyComponent.TopicBar
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

                MyComponent.TimePicker
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
                            MyComponent.TrainingTextNode{
                            innerIdx: index
                            titleText: trainProxy.getTrainingInfo(index,marco.trType)
                            timeText: trainProxy.getTrainingInfo(index,marco.trTime)
                            placeText: trainProxy.getTrainingInfo(index,marco.trAdd)
                            staffText: trainProxy.getTrainingInfo(index,marco.trStaff)

                            onNodeClicked:
                            {
                                trId = trainProxy.getTrainingInfo(index,marco.trTrid);
                                trainProxy.queryTrainingStaff(trId);
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
                                    if(nameList.model === 0)
                                        return;

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

                                MyComponent.NameList
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

                        MyComponent.Signature
                        {
                            id:signer
                            width:600
                            height:485

                            onFinished:
                            {
                                trainProxy.sign(trId,nameList.selectedStaffId,fileName,qmlHelper.getCurrAbsDateTime("yyyy-MM-dd HH:mm:ss"));
                            }

                            onError:
                            {
                                rootStackView.showMsg(error);
                            }
                        }
                    }
                }
            }
        }
    }
}
