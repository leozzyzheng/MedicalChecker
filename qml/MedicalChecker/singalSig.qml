import QtQuick 2.0
import "Component" as MyComponent

Rectangle {
    id:singalSigPage
    width: parent.width
    height: parent.height

    property bool isBusy: false

    MyComponent.TopBar
    {
        id:top
    }

    Rectangle
    {
        id:topicRect
        y:top.y + top.height
        height: topicBar.height
        width: singalSigPage.width

        MyComponent.TopicBar
        {
            id:topicBar
            topic: "SIGN"
        }
    }

    Rectangle
    {
        id:background
        width:singalSigPage.width
        height:singalSigPage.height - top.height - topicBar.height
        y:topicRect.y + topicRect.height

        Image
        {
            anchors.fill: parent
            fillMode: Image.Tile
            source:"qrc:/qml/Resource/background.png"
        }

        Rectangle
        {
            y:40
            width:950
            height:610
            color:"#00000000"
            anchors.horizontalCenter: parent.horizontalCenter

            Row
            {
                spacing:50

                Rectangle
                {
                    id:leftRect
                    width:300
                    height:620
                    radius: 5
                    border.color: marco.backBlue
                    border.width: 2

                    Column
                    {
                        Image
                        {
                            id:empPic
                            source:"qrc:/qml/Resource/title-emplyee.png"
                        }

                        Rectangle
                        {
                            clip:true
                            width:leftRect.width - leftRect.border.width*2
                            height:leftRect.height - leftRect.border.width*2 - empPic.height
                            x:leftRect.border.width

                            ListView
                            {
                                id:employeeList
                                anchors.fill: parent
                                model:0
                                delegate:
                                    MyComponent.CleanTextNode{
                                    width:employeeList.width
                                }
                            }
                        }
                    }
                }

                Rectangle
                {
                    id:rightRect
                    width:600
                    height:620
                    radius: 5
                    border.color: marco.backBlue
                    border.width: 2
                    clip:true

                    Column
                    {
                        Image
                        {
                            id:sigPic
                            source:"qrc:/qml/Resource/title-sign.png"
                        }

                        MyComponent.Signature
                        {
                            width:rightRect.width - rightRect.border.width*2
                            height:rightRect.height - rightRect.border.width*2 - sigPic.height
                            x:rightRect.border.width
                        }
                    }
                }
            }
        }



    }
}
