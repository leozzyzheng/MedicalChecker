import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import "Component"

Rectangle {
    width:parent.width
    height:parent.height

    Connections
    {
        target: initProxy

        onLoginFail:
        {
            console.log("passwd wrong");
        }

        onLoginSucc:
        {
            rootStackView.push({item:Qt.resolvedUrl("index.qml"),replace:true,destroyOnPop:true});
        }

        onError:
        {
            console.log(errorString);
        }
    }

    Rectangle
    {
        anchors.centerIn: parent
        width:512
        height:400

        Image
        {
            x:0
            y:0
            source: "qrc:/qml/Resource/login.png"
        }

        Rectangle
        {
            id:firstLine
            x:0
            z:100
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
                    text:"Clinic Name:"
                    font.family : marco.topicFontFa
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle
            {
                id: inputRect
                width:250
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
                    font.family : marco.topicFontFa
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
                        inputIndicator.height = 0;
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
                        indicatorRect.visible = false;
                    }

                    onHeightChanged:
                    {
                        indicatorRect.height = inputIndicator.height
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
            id:secondLine
            width:passwdLabel.width + passwdRect.width
            anchors.horizontalCenter: parent.horizontalCenter
            y:parent.height * 0.2 > height ? parent.height * 0.4 : height + 30

            Rectangle
            {
                x:0
                id:passwdLabel
                width:inputLabel.width
                height: passwdRect.height

                Text
                {
                    width:parent.width
                    height:passwdLabel.height
                    id:innerPasswdLabel
                    text:"PassWord:"
                    font.family : marco.topicFontFa
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Rectangle
            {
                id: passwdRect
                width:250
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
                    font.family : marco.topicFontFa
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
            y:parent.height * 0.2 > height ? parent.height * 0.6 : height + 30

            Image
            {
                id:loginBtn
                width:409
                height:93
                anchors.horizontalCenter: parent.horizontalCenter
                source:"qrc:/qml/Resource/btn-login.png"

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        console.log(passwdInput.text);
                        initProxy.login(nameInput.text, passwdInput.text);
                    }

                    onPressed:
                    {
                        loginBtn.source = "qrc:/qml/Resource/btn-login-click.png";
                    }

                    onReleased:
                    {
                        loginBtn.source = "qrc:/qml/Resource/btn-login.png";
                    }

                    onExited:
                    {
                        loginBtn.source = "qrc:/qml/Resource/btn-login.png";
                    }
                }
            }
        }
    }
}
