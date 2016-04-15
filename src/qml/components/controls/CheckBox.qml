import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

CheckBox {
    id: component

    property color borderColor: "black"
    property color handleColor: "black"
    property color fillColor: "orange"
    property bool lock: false

    enabled: !component.lock
    style: CheckBoxStyle {
        indicator: Rectangle {
            implicitHeight: control.height
            implicitWidth: control.width
            color: "transparent"
            border.width: 2
            border.color: component.borderColor

            // fill background
            Rectangle {
                id: fill

                width: (control.checked) ?parent.width - 2 * parent.border.width :0
                height: parent.height - 2 * parent.border.width
                color: component.fillColor

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.topMargin: parent.border.width
                anchors.leftMargin: parent.border.width

                Behavior on width {
                    NumberAnimation { duration: 50 }
                }
            }

            // handle
            Rectangle {
                id: handle

                x: fill.width - width * 0.33
                color: component.handleColor
                width: height / 10 * 3.
                height: parent.height
            }
        }
    }
}

