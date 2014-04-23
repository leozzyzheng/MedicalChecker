import QtQuick 2.0
import "Component"

Rectangle {
    width:parent.width
    height:parent.height

    Rectangle
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width:800
        height:600

        border.color: "black"
        border.width: 2

        Rectangle
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            id: inputRect
            width:400
            height:nameInput.height + 10
            border.color: "black"
            border.width: 1
            radius: 5

            TextInput
            {
                id:nameInput
                width:parent.width

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                text: ""
                font.family : "Consolas"
                font.pointSize: 14
                cursorVisible: true
                focus:true

                onTextChanged:
                {
                    if(nameInput.text == "")
                    {
                        inputIndicator.visible = false;
                        return;
                    }

                    initProxy.excuteIndicator(nameInput.text)
                    inputIndicator.model = 0;
                    inputIndicator.model = initProxy.getInfoNum();
                    console.log(initProxy.getInfoNum());
                    inputIndicator.visible = true;
                }
            }

            Component.onCompleted:
            {
                inputIndicator.maxHeight = inputRect.height * 5;
            }
        }

        Rectangle
        {
            clip:true
            width:nameInput.width;
            height: inputIndicator.height
            anchors.horizontalCenter: parent.horizontalCenter
            y:inputRect.y+inputRect.height
            z:10

            Indicator
            {
                id:inputIndicator
                width:nameInput.width;

                onClickedIndicator:
                {
                    nameInput.text = originName;
                    visible = false;
                }
            }
        }
    }
}
