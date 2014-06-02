import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:sterilizePage
    width: parent.width
    height: parent.height

    property bool isBusy: false

    Component.onCompleted:
    {
        qmlHelper.reset();
        sterProxy.queryTask();
    }

    Connections
    {
        target: sterProxy

        onTaskStandBy:
        {
            sterProxy.queryRecord(Qt.formatDateTime(new Date(),"HH:mm:ss"));
        }

        onCompleted:
        {
            icon.source = "qrc:/qml/Resource/disinfect-un.png";
            iconLabel.text = "All Sterilization Completed";
        }

        onNoTask:
        {
            icon.source = "qrc:/qml/Resource/disinfect-un.png";
            iconLabel.text = "No Task";
        }

        onRecordFound:
        {
            var id = qmlHelper.getData("nextId");
            iconLabel.text = "Next Task :\n"+ sterProxy.getData(id,marco.taskContent) +" Will Start At: \n"+sterProxy.getData(id,marco.sterSTime);
        }

        onRecordNotFound:
        {
            icon.source = "qrc:/qml/Resource/disinfect.png";
            var id = qmlHelper.getData("nextId");
            iconLabel.text = "This Task :\n"+ sterProxy.getData(id,marco.taskContent) +" Will End At: \n"+sterProxy.getData(id,marco.sterETime);
        }

        onNextId:
        {
            icon.source = "qrc:/qml/Resource/disinfect-un.png";
            iconLabel.text = "Getting Next Task ...";
            qmlHelper.setData("nextId",id);
        }

        onError:
        {
            console.log(errorString);
        }

        onSigSucc:
        {
            rootStackView.pop();
            rootStackView.showMsg("Successfully Confirm!");
            sterProxy.queryTask();
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
        width: sterilizePage.width

        MyComponent.TopicBar
        {
            id:topicBar
            topic: "DISINFECT"
        }
    }

    Rectangle
    {
        id:background
        width:sterilizePage.width
        height:sterilizePage.height - top.height - topicBar.height
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
            width:400
            height:430
            y:100
            anchors.horizontalCenter: parent.horizontalCenter
            color:"#00000000"

            Column
            {
                spacing: 80

                Rectangle
                {
                    id:timer
                    width:content.width
                    height:50
                    color:"#D5E2F8C8"
                    border.width: 2
                    border.color:"#7D8A90";
                    radius: 10

                    Timer
                    {
                        id:counter
                        interval: 1000; running: true; repeat: true
                        onTriggered:
                        {
                            t.text = Qt.formatDateTime(new Date(),"HH:mm:ss");
                        }
                    }

                    Timer
                    {
                        id:refresher
                        interval: 30000; running:true; repeat: true
                        onTriggered:
                        {
                            sterProxy.queryTask();
                        }
                    }

                    Text
                    {
                        id:t
                        anchors.centerIn: parent
                        font.family: marco.checkFontFa
                        font.pixelSize: 25
                        color: marco.fontBlue
                        text:Qt.formatDateTime(new Date(),"HH:mm:ss")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                Rectangle
                {
                    width:content.width
                    height:300
                    color:"#00000000"

                    Image
                    {
                        id:icon
                        anchors.centerIn: parent
                        source:"qrc:/qml/Resource/disinfect.png"
                    }

                    Rectangle
                    {
                        y:200
                        width:parent.width
                        height:100
                        color:"#00000000"

                        Text
                        {
                            id:iconLabel
                            anchors.centerIn: parent
                            text:"Conformed"
                            color:marco.fontBlue
                            font.family: marco.topicFontFa
                            font.pixelSize: 40
                        }
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            if(icon.source == "qrc:/qml/Resource/disinfect-un.png")
                                return;

                            if(sterProxy.getData(qmlHelper.getData("nextId"), marco.cleanSig) === "")
                                qmlHelper.setData("StaffId",sterProxy.getData(qmlHelper.getData("nextId"),marco.cleanStaffId));

                            qmlHelper.setData("TaskId",qmlHelper.getData("nextId"));
                            qmlHelper.setData("queryType","Ster");
                            rootStackView.push({item:Qt.resolvedUrl("singleSig.qml"),destroyOnPop:true});
                        }
                    }
                }
            }
        }
    }
}
