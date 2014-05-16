import QtQuick 2.0

ListView {
    id:list
    width:600

    signal nodeClicked (string name)
    property string selectedStaffId: ""

    model:0
    delegate:
        Rectangle{
        width:list.width
        height:30

        Text
        {
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            text:trainProxy.getSignInfo(index,marco.userName) + "|" + (trainProxy.getSignInfo(index,marco.trSign) === "" ? "Not Signed" : "Have Signed")
            font.family: marco.topicFontFa
        }

        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                selectedStaffId = trainProxy.getSignInfo(index,marco.trStaffid);
                nodeClicked(trainProxy.getSignInfo(index,marco.userName));
            }

            onReleased:
            {

            }

            onPressed:
            {


            }

            onExited:
            {

            }

            onCanceled:
            {

            }
        }
    }
}
