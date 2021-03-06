import QtQuick 2.0
import com.zzy.qmlcomponents 1.0
import QtQuick.Controls 1.1


Signature
{
    id : sig
    width:parent.width
    height:parent.height

    Rectangle
    {
        visible: sig.enabled ? false : true
        anchors.fill: parent
        z:1000
        color:"#CCCCCCCC"
    }

    signal send()

    onFinished:
    {
        console.log("filename: " + fileName);
    }

    onError:
    {
        rootStackView.showMsg(error);
        console.log("error: " + error);
    }

    Rectangle
    {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottomMargin: 10
        width:185
        height:30

        Row
        {
            spacing: 25
            Image
            {
                id:resetBtn
                source:"qrc:/qml/Resource/btn-reset.png"

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        sig.clearImage();
                    }

                    onPressed:
                    {
                        resetBtn.source = "qrc:/qml/Resource/btn-reset-click.png"
                    }

                    onReleased:
                    {
                        resetBtn.source = "qrc:/qml/Resource/btn-reset.png"
                    }

                    onExited:
                    {
                        resetBtn.source = "qrc:/qml/Resource/btn-reset.png"
                    }
                }
            }

            Image
            {
                id:okBtn
                source:"qrc:/qml/Resource/btn-ok.png"

                MouseArea
                {
                    anchors.fill: parent

                    onClicked:
                    {
                        send();
                    }

                    onPressed:
                    {
                        okBtn.source = "qrc:/qml/Resource/btn-ok-click.png"
                    }

                    onReleased:
                    {
                        okBtn.source = "qrc:/qml/Resource/btn-ok.png"
                    }

                    onExited:
                    {
                        okBtn.source = "qrc:/qml/Resource/btn-ok.png"
                    }
                }
            }
        }
    }
}
