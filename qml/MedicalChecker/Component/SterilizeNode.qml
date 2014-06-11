import QtQuick 2.0

Rectangle
{
    signal nodeClicked()
    property string labelText: ""
    property string sterId: ""
    property bool isConformed: true

    onLabelTextChanged:
    {
        if(labelText == "")
        {
            labelText == "No Task";
        }
    }

    width:icon.width
    height:icon.height
    color:"#00000000"

    Image
    {
        id:icon
        anchors.centerIn: parent
        source:isConformed ? "qrc:/qml/Resource/disinfect-un.png" : "qrc:/qml/Resource/disinfect.png"
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
            text:isConformed ?  labelText + " Conformed" : labelText
            color:marco.fontBlue
            font.family: marco.topicFontFa
            font.pixelSize: 25
            wrapMode: Text.WordWrap
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            if(isConformed)
                return;

            qmlHelper.setData("TaskId",sterId);
            qmlHelper.setData("queryType","Ster");
            rootStackView.push({item:Qt.resolvedUrl("../singleSig.qml"),destroyOnPop:true});

            nodeClicked();
        }
    }
}
