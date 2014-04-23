import QtQuick 2.0

Rectangle {
    signal btnClicked()
    signal btnPressed()
    signal btnReleased()

    property string btnNormalImage: ""
    property string btnPressedImage: ""

    width: 100
    height: 62

    Image
    {
        id:btnImage
        source:btnNormalImage
        anchors.fill: parent
        sourceSize.width: parent.width
        sourceSize.height: parent.height
    }

    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            btnClicked();
        }

        onPressed:
        {
            btnImage.source = btnPressedImage;
            btnPressed();
        }

        onReleased:
        {
            btnImage.source = btnNormalImage;
            btnReleased();
        }
    }
}
