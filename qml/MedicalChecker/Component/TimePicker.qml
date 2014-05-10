import QtQuick 2.0

Rectangle {
    signal decDate()
    signal incDate()

    width: 100
    height: 62

    Row
    {
        Image
        {
            width:60
            height:60
            id:decBtn
            source:"qrc:/qml/Resource/arrow-left-small.png"

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    decDate();
                }
            }
        }

        Rectangle
        {
            width:60
            height:60
            Text
            {
                width:60
                height:60
                id:dateText
                text:qmlHelper.getCurrWeekDay() + " " + qmlHelper.getCurrMonthName() + " " + qmlHelper.getCurrDateTime("dd") + " "
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

            }
        }

        Image
        {
            width:60
            height:60
            id:incBtn
            source:"qrc:/qml/Resource/arrow-right-small.png"

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    incDate();
                }
            }
        }
    }
}
