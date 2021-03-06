import QtQuick 2.0
import "../../controls" as Controls
import StyleSettings 1.0

SinglePanel {
    id: component

    property alias minimumValue: slider.minimumValue
    property alias maximumValue: slider.maximumValue
    property int precission: 0
    property alias pvalue: slider.value
    property alias lock: slider.lock
    signal valueChanged(var value)

    Controls.Slider {
        id: slider

        grooveWidth: 3
        handleSize: Qt.size(3, 15)
        height: 20
        width: 100

        activeColor: StyleSettings.primaryColor

        anchors.right: lineEdit.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        onValueChanged: component.valueChanged(slider.value)
    }

    Controls.LineEdit {
        id: lineEdit

        width: 40
        height: 22

        lock: slider.lock
        text: slider.value.toFixed(component.precission)
        textColor: StyleSettings.ternaryTextColor
        borderColor: StyleSettings.ternaryTextColor
        selectionColor: StyleSettings.primaryColor
        horizontalAlignment: TextInput.AlignRight
        validator: RegExpValidator { regExp: /\d+/ }

        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter

        onAccepted: {
            slider.value = parseInt(lineEdit.text)
        }
    }
}

