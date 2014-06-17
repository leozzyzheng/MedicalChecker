import QtQuick 2.0

Rectangle
{
    signal nodeClicked()
    property string labelText: ""
    property string sterId: ""
    property bool isConfirmed: true

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
        source:"qrc:/qml/Resource/disinfect.png"
    }

    Rectangle
    {
        y:200
        width:parent.width
        height:100
        color:"#00000000"
        clip:true

        Text
        {
            id:iconLabel
            anchors.centerIn: parent
            text:isConfirmed ?  labelText + "\n Last Check At:"+sterProxy.getData(index,marco.checkTime) : labelText
            color:marco.fontBlue
            font.family: marco.topicFontFa
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 25
            wrapMode: Text.WordWrap
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            qmlHelper.setData("TaskId",sterId);
            qmlHelper.setData("queryType","Ster");
            rootStackView.push({item:Qt.resolvedUrl("../singleSig.qml"),destroyOnPop:true});

            nodeClicked();
        }
    }
}
