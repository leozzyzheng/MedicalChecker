import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:checkPage
    width: parent.width
    height: parent.height

    property bool isBusy: false
    property int index: 0
    property bool reset: false

    MyComponent.TopBar
    {
        id:top
    }

    onResetChanged:
    {
        if(reset)
        {
            qmlHelper.reset();
            checkText.visible = false;
            checkBtn.visible = false;
            isChecked.visible = false;
            checkProxy.queryTask(qmlHelper.getCurrWeekDayNum());
            reset = false;
        }
    }

    Component.onCompleted:
    {
        qmlHelper.reset();
        checkProxy.queryTask(qmlHelper.getCurrWeekDayNum());
    }

    Connections
    {
        target: checkProxy

        onTaskDataStandBy:
        {
            checkProxy.queryRecord(qmlHelper.getCurrDateTime("yyyy-MM-dd"));
        }

        onNotChecked:
        {
            console.log("n")
            if(checkProxy.getTaskNum() === 0)
            {
                isChecked.visible = true;
                return;
            }

            checkText.visible = true;
            checkBtn.visible = true;
            checkText.text = checkProxy.getData(index++);
        }

        onIsChecked:
        {
            console.log("i")
            isChecked.visible = true;
        }

        onUpdateSucc:
        {
            reset = true;
            rootStackView.pop();
            rootStackView.showMsg("Successfully Check Off!");
        }

        onError:
        {
            console.log(errorString);
        }

        onNoTask:
        {
            isChecked.visible = true;
        }
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
            width:720
            height:450
            y:100
            anchors.horizontalCenter: parent.horizontalCenter
            color:"#FFFFFF"
            radius: 10
            clip:true

            Text
            {
                id:isChecked
                anchors.fill: parent
                font.family: marco.checkFontFa
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize:60
                color:marco.fontYellow
                visible: false
                text:"You have finished check-off today"
                wrapMode: Text.WordWrap
            }


            Text
            {
                id:checkText
                y:50
                width:parent.width
                font.family: marco.checkFontFa
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize:60//marco.checkFontpSize
                color:marco.fontDarkBlue
                visible: false
                wrapMode: Text.WordWrap
            }

            Image
            {
                id:checkBtn
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 45
                source:"qrc:/qml/Resource/checkoff-btn.png"
                visible: false

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        if(index === checkProxy.getTaskNum())
                        {
                            qmlHelper.setData("queryType","Check");
                            rootStackView.push({item:Qt.resolvedUrl("singleSig.qml"),destroyOnPop:true});
                        }
                        else
                        {
                            checkText.text = checkProxy.getData(index++);
                        }
                    }

                    onPressed:
                    {
                        checkBtn.source = "qrc:/qml/Resource/checkoff-btn-click.png";
                    }

                    onReleased:
                    {
                        checkBtn.source = "qrc:/qml/Resource/checkoff-btn.png";
                    }

                    onExited:
                    {
                        checkBtn.source = "qrc:/qml/Resource/checkoff-btn.png";
                    }
                }
            }
        }
    }
}
