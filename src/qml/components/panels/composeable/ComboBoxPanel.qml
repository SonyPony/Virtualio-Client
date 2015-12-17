import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

SinglePanel {
    id: panel

    property var model
    property var currentItem: comboBox.currentItem

    Controls.StyledComboBox {
        id: comboBox

        model: panel.model
        width: 100
        height: 20

        anchors.right: parent.right
        anchors.rightMargin: height
        anchors.verticalCenter: parent.verticalCenter
    }
}

