import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

SinglePanel {
    id: component

    property string placeHolderText: ""
    property alias text: lineEdit.text
    signal valueChanged(var value)

    onValueChanged: console.log(value)

    Controls.LineEdit {
        id: lineEdit

        width: 100
        height: 22

        placeholderText: component.placeHolderText
        placeHolderTextColor: StyleSettings.primaryTextColor
        textColor: StyleSettings.ternaryTextColor
        borderColor: StyleSettings.ternaryTextColor
        selectionColor: StyleSettings.primaryColor

        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        onAccepted: component.valueChanged(lineEdit.text)
    }
}

