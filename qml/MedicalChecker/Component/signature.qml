import QtQuick 2.0
import com.zzy.qmlcomponents 1.0


Signature
{
    id : sig

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
            sig.sendImage("ganggedajj");
        }
    }
}
