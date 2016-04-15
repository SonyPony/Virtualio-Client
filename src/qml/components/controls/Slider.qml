import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Slider {
    id: component

    property color handleColor: "gray"
    property color grooveColor: "lightGray"
    property color activeColor: "orange"
    property real grooveWidth: component.height / 3
    property size handleSize: Qt.size(component.height / 3, component.height)
    property bool lock: false

    MouseArea {
        anchors.fill: parent
        enabled: component.lock
    }

    style: SliderStyle {
        groove: Rectangle {
            implicitWidth: component.width
            implicitHeight: component.grooveWidth
            color: control.grooveColor

            Rectangle {
                implicitHeight: parent.implicitHeight
                implicitWidth: (control.value - control.minimumValue) / (control.maximumValue - control.minimumValue) * parent.implicitWidth
                color: control.activeColor
            }
        }

        handle: Rectangle {
            implicitWidth: component.handleSize.width
            implicitHeight: component.handleSize.height
            color: component.handleColor
        }
    }
}

