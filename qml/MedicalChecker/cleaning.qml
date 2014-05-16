import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:cleanPage
    width: parent.width
    height: parent.height

    property bool isBusy: false

    function changeDate(delta)
    {
        qmlHelper.addDay(delta);

        dailyCleanProxy.abort();
        weeklyCleanProxy.abort();
        supplyProxy.abort();

        dailyCleanProxy.queryDaily();
        weeklyCleanProxy.queryWeekly();
        supplyProxy.querySupply();
    }

    Component.onCompleted:
    {
        qmlHelper.reset();
        dailyCleanProxy.queryDaily();
        weeklyCleanProxy.queryWeekly();
        supplyProxy.querySupply();
    }

    Connections
    {
        target: dailyCleanProxy

        onTaskContentStandBy:
        {
            dailyCleanProxy.queryDailyRecord(qmlHelper.getCurrDateTime("yyyy-MM-dd"));
        }

        onRecordStandBy:
        {
            dailyList.model = 0;
            dailyList.model = dailyCleanProxy.getTaskNum();
        }

        onUpdateSucc:
        {
            rootStackView.pop();
            rootStackView.showMsg("Successfully Sign!");
            dailyCleanProxy.queryDaily();
        }
    }

    Connections
    {
        target: weeklyCleanProxy

        onTaskDataStandBy:
        {
            weeklyCleanProxy.queryRecord(qmlHelper.getCurrWeekNum());
        }

        onRecordDataStandBy:
        {
            weeklyList.model = 0;
            weeklyList.model = weeklyCleanProxy.getTaskNum();
        }

        onUpdateSucc:
        {
            rootStackView.pop();
            rootStackView.showMsg("Successfully Sign!");
            weeklyCleanProxy.queryWeekly();
        }
    }

    Connections
    {
        target: supplyProxy

        onTaskDataStandBy:
        {
            supplyProxy.queryRecord(qmlHelper.getCurrDateTime("yyyy-MM-dd"));
        }

        onRecordDataStandBy:
        {
            supplyList.model = 0;
            supplyList.model = supplyProxy.getTaskNum();
        }

        onUpdateSucc:
        {
            rootStackView.pop();
            rootStackView.showMsg("Successfully Sign!");
            supplyProxy.querySupply();
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
        width: cleanPage.width

        MyComponent.TopicBar
        {
            id:topicBar
            topic: "CLEANING"
        }
    }

    Rectangle
    {
        id:background
        width:cleanPage.width
        height:cleanPage.height - top.height - topicBar.height
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
            y:39
            anchors.horizontalCenter: parent.horizontalCenter
            color:"#00000000"

            Row
            {
                spacing: 50

                Column
                {
                    spacing: 20

                    Rectangle
                    {
                        width:450
                        height:56
                        color:"#00000000"

                        MyComponent.TimePicker
                        {
                            width:400
                            anchors.centerIn: parent
                            id:picker

                            onDecDate:
                            {
                                changeDate(-1);
                            }

                            onIncDate:
                            {
                                changeDate(1);
                            }
                        }
                    }

                    Rectangle
                    {
                        id:dailyRect
                        width:450
                        height:545
                        clip:true
                        radius: 5
                        border.color: marco.backBlue
                        border.width: 2

                        Column
                        {
                            Image
                            {
                                id:dailyPic
                                source:"qrc:/qml/Resource/title-daily.png"
                            }

                            Rectangle
                            {
                                clip:true;
                                width:dailyRect.width - dailyRect.border.width*2
                                height:dailyRect.height - dailyRect.border.width*2 - dailyPic.height
                                x:dailyRect.border.width

                                ListView
                                {
                                    id:dailyList
                                    anchors.fill: parent
                                    model:0
                                    delegate:
                                        MyComponent.CleanTextNode{
                                        backColor: (index+1)%2 == 0 ? marco.backGray : "#FFFFFF"
                                        innerText: (index+1) + "." + dailyCleanProxy.getData(index,marco.taskContent)

                                        Component.onCompleted:
                                        {
                                            if(dailyCleanProxy.getData(index, marco.cleanSig) === "")
                                            {
                                                imgSrc = "";
                                            }
                                            else
                                            {
                                                canClicked = false;
                                            }
                                        }

                                        onNodeClicked:
                                        {
                                            qmlHelper.setData("TaskContent",dailyCleanProxy.getData(index,marco.taskContent));

                                            if(dailyCleanProxy.getData(index, marco.cleanSig) === "")
                                                qmlHelper.setData("StaffId",dailyCleanProxy.getData(index,marco.cleanStaffId));

                                            qmlHelper.setData("queryType","Daily");
                                            rootStackView.push({item:Qt.resolvedUrl("singleSig.qml"),destroyOnPop:true});
                                        }
                                    }
                                }
                            }


                        }
                    }
                }

                Column
                {
                    spacing: 37

                    Rectangle
                    {
                        id:weeklyRect
                        width:450
                        height:280
                        clip:true
                        radius: 5
                        border.color: marco.backBlue
                        border.width: 2

                        Column
                        {
                            Image
                            {
                                id:weeklyPic
                                source:"qrc:/qml/Resource/title-weeely.png"
                            }

                            Rectangle
                            {
                                clip:true;
                                width:weeklyRect.width - weeklyRect.border.width*2
                                height:weeklyRect.height - weeklyRect.border.width*2 - weeklyPic.height
                                x:weeklyRect.border.width

                                ListView
                                {
                                    id:weeklyList
                                    anchors.fill: parent
                                    model:0
                                    delegate:
                                        MyComponent.CleanTextNode{
                                        backColor: (index+1)%2 == 0 ? marco.backGray : "#FFFFFF"
                                        innerText: (index+1) + "." + weeklyCleanProxy.getData(index,marco.taskContent)

                                        Component.onCompleted:
                                        {
                                            if(weeklyCleanProxy.getData(index, marco.cleanSig) === "")
                                            {
                                                imgSrc = "";
                                            }
                                            else
                                            {
                                                canClicked = false;
                                            }
                                        }

                                        onNodeClicked:
                                        {
                                            qmlHelper.setData("TaskContent",weeklyCleanProxy.getData(index,marco.taskContent));

                                            if(weeklyCleanProxy.getData(index, marco.cleanSig) === "")
                                                qmlHelper.setData("StaffId",weeklyCleanProxy.getData(index,marco.cleanStaffId));

                                            qmlHelper.setData("queryType","Weekly");
                                            rootStackView.push({item:Qt.resolvedUrl("singleSig.qml"),destroyOnPop:true});
                                        }
                                    }
                                }
                            }
                        }
                    }

                    Rectangle
                    {
                        id:supplyRect
                        width:450
                        height:300
                        clip:true
                        radius: 5
                        border.color: marco.backBlue
                        border.width: 2

                        Column
                        {
                            Image
                            {
                                id:supplyPic
                                source:"qrc:/qml/Resource/title-supply.png"
                            }

                            Rectangle
                            {
                                width:supplyRect.width - supplyRect.border.width*2
                                height:supplyRect.height - supplyRect.border.width*2 - supplyPic.height
                                x:supplyRect.border.width
                                clip:true

                                GridView
                                {
                                    id:supplyList
                                    anchors.fill: parent
                                    flow:GridView.TopToBottom
                                    flickableDirection: Flickable.HorizontalFlick
                                    model:0
                                    delegate:
                                        MyComponent.SupplyNode{
                                        iconText: supplyProxy.getData(index,marco.taskContent);

                                        onNodeClicked:
                                        {
                                            qmlHelper.setData("TaskContent",supplyProxy.getData(index,marco.taskContent));

                                            if(supplyProxy.getData(index, marco.cleanSig) === "")
                                                qmlHelper.setData("StaffId",supplyProxy.getData(index,marco.cleanStaffId));

                                            qmlHelper.setData("queryType","Supply");
                                            rootStackView.push({item:Qt.resolvedUrl("singleSig.qml"),destroyOnPop:true});
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
