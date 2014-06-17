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
            sterProxy.queryRecord(Qt.formatDateTime(new Date(),"yyyy-MM-dd"));
        }

        onNoTask:
        {
            list.model = 1;
//            icon.source = "qrc:/qml/Resource/disinfect-un.png";
//            iconLabel.text = "No Task";
        }

        onRecordStandBy:
        {
            list.model = 0;
            list.model = sterProxy.getNum();
        }

//        onRecordFound:
//        {
//            icon.source = "qrc:/qml/Resource/disinfect-un.png";
//            var id = qmlHelper.getData("nextId");
//            iconLabel.text = "Next Task :\n"+ sterProxy.getData(id,marco.taskContent) +" Will Start At: \n"+sterProxy.getData(id,marco.sterSTime);
//        }

//        onRecordNotFound:
//        {
//            icon.source = "qrc:/qml/Resource/disinfect.png";
//            var id = qmlHelper.getData("nextId");
//            iconLabel.text = "This Task :\n"+ sterProxy.getData(id,marco.taskContent) +" Will End At: \n"+sterProxy.getData(id,marco.sterETime);
//        }

//        onNextId:
//        {
//            icon.source = "qrc:/qml/Resource/disinfect-un.png";
//            iconLabel.text = "Getting Next Task ...";
//            qmlHelper.setData("nextId",id);
//        }

        onError:
        {
            //icon.source = "qrc:/qml/Resource/disinfect-un.png";
            //iconLabel.text = "No Task";
            console.log(errorString);
        }

        onSigSucc:
        {
            rootStackView.pop();
            rootStackView.showMsg("Successfully Confirm!");
            sterProxy.queryTask();
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
        //clip: true

        Image
        {
            anchors.fill: parent
            fillMode: Image.Tile
            source:"qrc:/qml/Resource/background.png"
        }

        ListView
        {
            id:list
            orientation: ListView.Horizontal
            anchors.centerIn: background
            spacing: 20

            model:0
            delegate:
                MyComponent.SterilizeNode{
                    sterId: sterProxy.getData(index,marco.sterId)
                    labelText: sterProxy.getData(index,marco.taskContent)
                    isConfirmed: sterProxy.getData(index,marco.cleanSig) == "" ? false : true

                    onNodeClicked:
                    {

                    }

                    Component.onCompleted:
                    {
                        list.height = height;

                        if(list.width == background.width)
                            return;

                        if(list.width + width > background.width)
                        {
                            list.width = background.width;
                        }
                        else
                        {
                            list.width += width;
                        }
                    }
            }
        }
    }
}
