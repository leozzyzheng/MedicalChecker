import QtQuick 2.0
import "Component"

Rectangle {
    width: parent.width
    height: parent.height

    TopicBar
    {

    }

    Component.onCompleted:
    {
        trainProxy.queryTraining();
    }

    Connections
    {
        target:trainProxy

        onError:
        {
            console.log(errorString);
        }
    }

    TimePicker
    {

    }
}
