import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

Rectangle {
    id: component

    property int verticalMargins: 10
    property string name: "Type"
    property var model: ["1", "2", "3"]
    signal completed
    property alias currentItem: radioButtons.currentItem
    property alias lock: radioButtons.lock
    property alias currentItemSetter: radioButtons.currentItemSetter

    color: "transparent"
    height: radioButtons.height + label.height + 3 * verticalMargins

    Text {
        id: label

        text: component.name
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
        model: component.model

        anchors.left: label.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: component.verticalMargins
    }
}

