import QtQuick 2.0
import com.zzy.qmlcomponents 1.0
import QtQuick.Controls 1.1


Signature
{
    id : sig
    opacity : 1

    onFinished:
    {
        console.log("filename: " + fileName);
    }

    onError:
    {
        console.log("error: " + error);
    }

    MouseArea
    {
        width:50
        height:50
        onClicked:
        {
            sig.sendImage("clinica");
        }
    }

    StackViewDelegate
    {
        id: selftDelegate
    }
}
