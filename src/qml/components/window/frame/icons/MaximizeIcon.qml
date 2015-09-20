import QtQuick 2.0

Icon {
    id: icon

    clip: true
    state: "maximize"

    Rectangle {
        color: parent.iconColor
        radius: width / 4

        width: parent.size / 2
        height: width

        anchors.centerIn: parent
    }

    Rectangle {
        id: line

        rotation: 315
        color: parent.frameColor

        height: parent.size
        width: parent.size / 6

        anchors.centerIn: parent

        Behavior on height {
            NumberAnimation { easing.type: Easing.InOutQuad; duration: 500 }
        }
    }

    states: [
        State {
            name: "maximize"
            PropertyChanges { target: line; height: icon.size * 1.5}
        },

        State {
            name: "window"
            PropertyChanges { target: line; height: 0}
        }
    ]
}

