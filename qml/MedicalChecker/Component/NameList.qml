import QtQuick 2.0

ListView {
    id:list
    width:600

    signal nodeClicked (string name)

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
            text:trainProxy.getSignInfo(index,marco.trStaffid) + "|" + trainProxy.getSignInfo(index,marco.trSign)
            font.family: marco.topicFontFa
        }

        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                nodeClicked(trainProxy.getSignInfo(index,marco.trStaffid));
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
