import QtQuick 2.0

Rectangle {
    signal decDate()
    signal incDate()

    function updateText()
    {
        dateText.text = qmlHelper.getCurrWeekDay() + " " + qmlHelper.getCurrMonthName() + " " + qmlHelper.getCurrDateTime("dd") + " ";
    }

    id:timePicker
    width: 300
    height: 28*2
    radius: 10

    Row
    {
        Rectangle
        {
            id:decBtn
            height:28*2
            width:21*2
            radius: 10

            Image
            {
                anchors.centerIn: parent
                source:"qrc:/qml/Resource/arrow-left-small.png"
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    qmlHelper.addDay(-1);
                    updateText();
                    decDate();
                }
            }
        }



        Rectangle
        {
            width:timePicker.width - decBtn.width - incBtn.width
            height:timePicker.height

            Text
            {
                anchors.fill: parent
                width:60
                height:60
                id:dateText
                text:qmlHelper.getCurrWeekDay() + " " + qmlHelper.getCurrMonthName() + " " + qmlHelper.getCurrDateTime("dd") + " "
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: marco.topicFontFa
                color: marco.fontBlue
            }
        }

        Rectangle
        {
            id:incBtn
            height:28*2
            width:21*2
            radius: 10

            Image
            {
                anchors.centerIn: parent
                source:"qrc:/qml/Resource/arrow-right-small.png"
            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    qmlHelper.addDay(1);
                    updateText();
                    incDate();
                }
            }
        }


    }
}
