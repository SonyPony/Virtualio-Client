import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

Rectangle {
    id: component

    property int verticalMargins: 10
    property string label: "Type"
    property var model: ["SPI", "SDA", "UART"]
    signal completed

    color: "transparent"
    height: radioButtons.height + label.height + 3 * verticalMargins

    Text {
        id: label

        text: component.label
        color: StyleSettings.ternaryTextColor

        font.pixelSize: 15

        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: component.verticalMargins

        Component.onCompleted: component.completed()
    }

    Controls.RadioButtonsGroup {
        id: radioButtons

        checkedColor: StyleSettings.primaryColor

        anchors.left: label.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: component.verticalMargins
    }
}

