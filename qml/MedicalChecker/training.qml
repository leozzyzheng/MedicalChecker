import QtQuick 2.0

Rectangle {
    width: parent.width
    height: parent.height
    Component.onCompleted:
    {
        trainProxy.queryTraining();
        console.log(marco.trTime);
    }

    Connections
    {
        target:trainProxy

        onError:
        {
            console.log(errorString);
        }
    }
}
