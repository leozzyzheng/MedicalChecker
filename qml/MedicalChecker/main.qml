import QtQuick 2.0
import QtQuick.Controls 1.1

import "Component" as MyComponent

StackView
{
    property int waitingTime: 0
    property int logestWaitingTime: 30000

    //for test
    width:1024
    height:768

    function resetDelegate()
    {
        delegate = defaultDelegate;
    }

    function exit()
    {
        Qt.quit();
    }

    function showMsg(msg)
    {
        messageBox.msg = msg;
        messageBox.show();
    }

    id: rootStackView

    MyComponent.Message
    {
        id:messageBox
        anchors.horizontalCenter: parent.horizontalCenter
        y:parent.height*0.8
        z:1000
        visible:false
    }

    Connections
    {
        target: initProxy

        onNotOpened:
        {
            if(waitingTime > logestWaitingTime)
            {
                console.log("wait for too long! Quit now.");
                Qt.quit();
            }

            initTimer.interval = 500;
            initTimer.running = true;
            waitingTime += 500;
        }
    }

    Timer
    {
        id: initTimer
        interval: 1000; running: false; repeat: false
        onTriggered:
        {
            initProxy.excuteInit();
        }
    }

    Component.onCompleted:
    {
        push({item:Qt.resolvedUrl("startup.qml"),destroyOnPop:true});
        initTimer.running = true;
    }

    StackViewDelegate {

        id:defaultDelegate

        function transitionFinished(properties)
        {
            properties.exitItem.x = 0
            properties.exitItem.rotation = 0
        }

        pushTransition: StackViewTransition {
            SequentialAnimation {
                ScriptAction {
                    script: enterItem.rotation = 90
                }
                PropertyAnimation {
                    target: enterItem
                    property: "x"
                    from: enterItem.width
                    to: 0
                }
                PropertyAnimation {
                    target: enterItem
                    property: "rotation"
                    from: 90
                    to: 0
                }
            }
            PropertyAnimation {
                target: exitItem
                property: "x"
                from: 0
                to: -exitItem.width
            }
        }
    }
}

