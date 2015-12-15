import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Slider {
    id: component

    property color handleColor: "gray"
    property color grooveColor: "lightGray"
    property color activeColor: "orange"

    style: SliderStyle {
        groove: Rectangle {
            implicitWidth: component.width
            implicitHeight: component.height / 3
            color: control.grooveColor

            Rectangle {
                implicitHeight: parent.implicitHeight
                implicitWidth: (control.value - control.minimumValue) / (control.maximumValue - control.minimumValue) * parent.implicitWidth
                color: control.activeColor
            }
        }

        handle: Rectangle {
            implicitWidth: component.height / 3
            implicitHeight: component.height
            color: component.handleColor
        }
    }
}

