import QtQuick 2.0
import QtQuick.Controls 1.1

import "Component"

StackView
{
    function resetDelegate()
    {
        delegate = defaultDelegate;
    }

    function exit()
    {
        Qt.quit();
    }

    id: rootStackView

    initialItem: Qt.resolvedUrl("startup.qml");

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

