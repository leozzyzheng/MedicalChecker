import QtQuick 2.0

Rectangle {

    property string iconSrc: "qrc:/qml/Resource/icon-training.png"
    property string iconClickSrc: "qrc:/qml/Resource/icon-training-click.png"
    property string qmlSrc: "training.qml"
    property string labelText: "TRAINING"

    id:component
    width: 200
    height: 200
    radius: 10

    Image
    {
        id:componentImg
        anchors.horizontalCenter: parent.horizontalCenter
        source:iconSrc
    }

    Rectangle
    {
        width:parent.width
        height:parent.height - componentImg.height
        y:componentImg.y + componentImg.height
        radius: 10

        Text
        {
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.family: marco.topicFontFa
            text:labelText
            color:marco.fontBlue
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            rootStackView.push({item:Qt.resolvedUrl("../" + qmlSrc)});
        }

        onPressed:
        {
            componentImg.source = iconClickSrc;
        }

        onReleased:
        {
            componentImg.source = iconSrc;
        }

        onExited:
        {
            componentImg.source = iconSrc;
        }
    }
}
