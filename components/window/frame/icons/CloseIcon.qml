import QtQuick 2.0

Icon {
    Rectangle {
        color: parent.iconColor
        rotation: 45

        width: parent.size / 1.3
        height: parent.size / 6
        radius: height / 2

        anchors.centerIn: parent
    }

    Rectangle {
        color: parent.iconColor
        rotation: 315

        width: parent.size / 1.3
        height: parent.size / 6
        radius: height / 2

        anchors.centerIn: parent
    }
}

