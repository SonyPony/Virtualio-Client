import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import "../../static/responsivity/responsivity.js" as RL

TextField {
    id: component

    property color placeHolderTextColor
    property color borderColor
    property color selectionColor
    property int borderWidth: 1

    style: TextFieldStyle {
        placeholderTextColor: component.placeHolderTextColor
        selectionColor: component.selectionColor
        background: Rectangle {
            color: "transparent"
            border.color: component.borderColor
            border.width: component.borderWidth
        }
    }
}

