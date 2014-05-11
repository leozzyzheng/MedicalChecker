import QtQuick 2.0
import com.zzy.qmlcomponents 1.0
import QtQuick.Controls 1.1


Signature
{
    id : sig
    width:parent.width
    height:parent.height

    onFinished:
    {
        console.log("filename: " + fileName);
    }

    onError:
    {
        console.log("error: " + error);
    }
}
