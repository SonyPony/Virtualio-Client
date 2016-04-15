import QtQuick 2.0
import "../auxiliary"

Item {
    id: lockPanel

    property color color
    property color interactiveMarkColor
    property int lockedPartHeight: height - interactivePartHeight
    property int interactivePartHeight

    clip: true

    Rectangle {
        id: line
        color: lockPanel.color

        width: 5
        height: lockedPartHeight
        anchors.top: parent.top
        anchors.right: parent.right


        Rectangle {
            id: interactiveMark

            width: parent.width
            height: interactivePartHeight
            color: interactiveMarkColor

            anchors.top: parent.bottom
            anchors.right: parent.right

            Behavior on color {
                ColorAnimation { duration: 200 }
            }
        }
    }

    Rectangle {
        id: lockContainer

        width: parent.width
        height: width
        color: lockPanel.color

        Image {
            width: parent.width / 2.5
            source: "qrc:/resources/images/lockIcon.svg"
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent

            sourceSize.width: width
        }
    }

    Triangle {
        width: parent.width
        height: width
        color: lockPanel.color
        rotation: -90
        inverted: true
        rightAngle: true
        anchors.top: lockContainer.bottom
    }

    transform: Rotation {
        id: lockAnimation
        origin.x: lockPanel.width
        origin.y: 0

        angle: -90
        axis { x: 0; y: 1; z: 0 }

        Behavior on angle {
            NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
        }
    }

    function show() { lockAnimation.angle = 0 }
    function hide() { lockAnimation.angle = -90 }
}
