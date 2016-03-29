import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

SinglePanel {
    id: panel

    property var model
    property alias currentItem: comboBox.currentItem
    property alias _dropDown: comboBox._dropDown
    property alias _comboBox: comboBox
    signal hideDropDown(var obj)
    signal showDropDown(var obj)

    Controls.StyledComboBox {
        id: comboBox

        model: panel.model
        width: 100
        height: 20

        anchors.right: parent.right
        anchors.rightMargin: height
        anchors.verticalCenter: parent.verticalCenter

        onHideDropDown: panel.hideDropDown(panel)
        onShowDropDown: panel.showDropDown(panel)
    }
}

