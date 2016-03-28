import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

SinglePanel {
    id: component

    property alias checked: checkbox.checked
    signal valueChanged(var value)

    Controls.CheckBox {
        id: checkbox

        width: 50
        height: 20

        borderColor: StyleSettings.ternaryTextColor
        handleColor: "lightGray"
        fillColor: StyleSettings.primaryColor

        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        onCheckedChanged: component.valueChanged(checkbox.checked)
    }
}

