import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import "Component"

Rectangle {
    width:parent.width
    height:parent.height

    Rectangle
    {
        anchors.centerIn: parent
        width:800
        height:600

        border.color: "black"
        border.width: 2

        Rectangle
        {
            width:inputLabel.width + inputRect.width
            anchors.horizontalCenter: parent.horizontalCenter
            y:parent.height * 0.2

            Rectangle
            {
                x:0
                id:inputLabel
                width:innerInputLabel.width
                height: inputRect.height

                Text
                {
                    height:inputLabel.height
                    id:innerInputLabel
                    text:"UserName:"
                    font.family : "Consolas"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle
            {
                id: inputRect
                width:400
                height:nameInput.height + 10
                border.color: "black"
                border.width: 1
                radius: 5
                x:inputLabel.x + inputLabel.width + 10

                TextInput
                {
                    x: 10
                    id:nameInput
                    width:parent.width - 20
                    anchors.centerIn: parent

                    text: ""
                    font.family : "Consolas"
                    font.pointSize: 14
                    cursorVisible: true
                    focus:true
                    clip: true

                    onTextChanged:
                    {
                        if(nameInput.text == "")
                        {
                            indicatorRect.visible = false;
                            return;
                        }

                        initProxy.excuteIndicator(nameInput.text)

                        if(initProxy.getInfoNum() === 0)
                        {
                            indicatorRect.visible = false;
                            return;
                        }

                        //console.log(initProxy.getInfoNum());

                        inputIndicator.model = 0;
                        inputIndicator.model = initProxy.getInfoNum();
                        inputIndicator.visible = true;
                        indicatorRect.visible = true;
                    }
                }
            }

            Rectangle
            {
                id:indicatorRect
                clip:true
                width:nameInput.width;
                height:inputIndicator.height
                y:inputRect.y+inputRect.height
                x:inputRect.x
                visible:false

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

            Component.onCompleted:
            {
                inputIndicator.maxHeight = inputRect.height * 5;
            }
        }

        Rectangle
        {
            width:passwdLabel.width + passwdRect.width
            anchors.horizontalCenter: parent.horizontalCenter
            y:parent.height * 0.1 > height ? parent.height * 0.3 : height + 30

            Rectangle
            {
                x:0
                id:passwdLabel
                width:innerPasswdLabel.width
                height: passwdRect.height

                Text
                {
                    height:passwdLabel.height
                    id:innerPasswdLabel
                    text:"PassWord:"
                    font.family : "Consolas"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle
            {
                id: passwdRect
                width:400
                height:passwdInput.height + 10
                border.color: "black"
                border.width: 1
                radius: 5
                x:passwdLabel.x + passwdLabel.width + 10

                TextInput
                {
                    x: 10
                    id:passwdInput
                    width:parent.width - 20
                    anchors.centerIn: parent

                    text: ""
                    font.family : "Consolas"
                    font.pointSize: 14
                    focus: false
                    clip: true
                    echoMode: TextInput.Password
                }
            }
        }

        Rectangle
        {
            width:passwdLabel.width + passwdRect.width
            anchors.horizontalCenter: parent.horizontalCenter
            y:parent.height * 0.1 > height ? parent.height * 0.4 : height + 30

            Button
            {
                width:130
                height:40
                anchors.horizontalCenter: parent.horizontalCenter

                style:
                    ButtonStyle{
                    label:Text
                    {
                        text:"Login"
                        font.family : "Consolas"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                onClicked:
                {
                    console.log(passwdInput.text);
                }
            }
        }
    }
}
