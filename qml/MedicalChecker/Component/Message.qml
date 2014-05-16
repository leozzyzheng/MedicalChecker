import QtQuick 2.0

Rectangle {
    property string msg: "msg"

    function show()
    {
        visible = true;
        animation.restart();
    }

    id:rect
    width: 400
    height: innerText.height + 10
    color: "#b3292323"
    radius: 20
    border.width: 0

    Text
    {
        y:5
        id:innerText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        width:parent.width
        font.family: marco.topicFontFa
        color:marco.fontWhite
        text:msg
        wrapMode: Text.WordWrap
    }

    PropertyAnimation
    {
        id: animation
        target: rect
        property: "opacity"
        from:5
        to: 0
        duration:2500
        running: false

        onStopped:
        {
            if(rect.opacity == 0)
                rect.visible = false;
        }
    }
}
