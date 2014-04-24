import QtQuick 2.0


Rectangle {
    width: parent.width;
    height: parent.height;

    property string checkoff: "Daily Checkoff"
    property string cleaning: "Daily Cleaning"
    property string training: "Tranning check"
    property string sterilization: "Daily Sterilization"

    property string checkoffImage: "qrc:/qml/Resource/stratup.jpg"
    property string cleaningImage: "qrc:/qml/Resource/stratup.jpg"
    property string trainingImage: "qrc:/qml/Resource/stratup.jpg"
    property string sterilizationImage: "qrc:/qml/Resource/stratup.jpg"

    ListModel {
        id:indexModel

        //only in this way can add property by script
        Component.onCompleted: {
            indexModel.append({"name":training,"icon":trainingImage});
            indexModel.append({"name":cleaning,"icon":cleaningImage});
            indexModel.append({"name":checkoff,"icon":checkoffImage});
            indexModel.append({"name":sterilization,"icon":sterilizationImage});
        }
    }

    Component {
        id: delegate
        Column {
            z:wrapper.PathView.isCurrentItem ? 1:-1
            id: wrapper

            Image {
                anchors.horizontalCenter: nameText.horizontalCenter
                width: 64; height: 64
                source: icon

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        if(nameText.text == checkoff)
                            rootStackView.push({item:Qt.resolvedUrl("checkoff.qml"),replace:false});
                        else if(nameText.text == cleaning)
                            rootStackView.push({item:Qt.resolvedUrl("cleaning.qml"),replace:false});
                        else if(nameText.text == training)
                            rootStackView.push({item:Qt.resolvedUrl("training.qml"),replace:false});
                        else if(nameText.text == sterilization)
                            rootStackView.push({item:Qt.resolvedUrl("sterilization.qml"),replace:false});
                        else
                            console.log("What's the" + nameText.text + "????");
                    }
                }
            }
            Text {
                id: nameText
                text: name
                font.pointSize: 16
                color: wrapper.PathView.isCurrentItem ? "red" : "black"
            }
        }
    }

    PathView {
        anchors.fill: parent
        model: indexModel
        delegate: delegate
        path: Path {
            startX: 520; startY: 500
            PathQuad { x: 520; y: 425; controlX: 660; controlY: 475 }
            PathQuad { x: 520; y: 500; controlX: 380; controlY: 475 }
        }
    }
}
