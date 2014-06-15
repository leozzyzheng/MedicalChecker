import QtQuick 2.0

ListView {
    id:list
    width:600

    signal nodeClicked (string name)
    property string selectedStaffId: ""

    model:0
    delegate:
        Rectangle{
        id:delegateRect
        width:list.width
        height:60
        border.width: 1
        border.color: "black"
        color:trainProxy.getSignInfo(index,marco.trSign) == "" ? "#FFFFFF":marco.backBlue

        Text
        {
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent
            text:trainProxy.getSignInfo(index,marco.userName)
            font.family: marco.topicFontFa
        }

        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                console.log(trainProxy.getSignInfo(index,marco.trSign));
                //do not change == to ===
                if(delegateRect.color == marco.backBlue)
                {
                    nodeClicked("");
                    return;
                }

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
