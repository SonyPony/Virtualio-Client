import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    id: component

    property string label: "Type"

    color: "transparent"

    Text {
        text: component.label
        color: StyleSettings.ternaryTextColor

        font.pixelSize: 15

        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
    }
}

