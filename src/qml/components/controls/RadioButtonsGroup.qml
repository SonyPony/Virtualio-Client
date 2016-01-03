import QtQuick 2.0
import StyleSettings 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id: component

    property font font: root.defaultFont
    property color textColor: "lightGray"
    property color outlineColor: textColor
    property color checkedColor: "orange"
    property var model: []
    property string currentItem: model[0]

    height: model.length * (17 + 8) - 8

    ExclusiveGroup { id: rbExclusiveGroup }

    Column {
        spacing: 8
        Repeater {
            model: component.model
            delegate: RadioButton {
                antialiasing: true
                text: modelData
                exclusiveGroup: rbExclusiveGroup
                style: RadioButtonStyle {
                    label: Text {
                        text: control.text
                        color: component.textColor
                        font: component.font
                    }

                    indicator: Rectangle {
                        implicitWidth: 17
                        implicitHeight: implicitWidth

                        color: "transparent"
                        radius: implicitHeight
                        border.width: 1
                        border.color: component.outlineColor

                        Rectangle {
                            implicitWidth: 9
                            implicitHeight: implicitWidth

                            color: component.checkedColor
                            opacity: control.checked
                            radius: implicitHeight
                            anchors.centerIn: parent

                            Behavior on opacity {
                                NumberAnimation { duration: 200 }
                            }
                        }
                    }
                }
            }
        }
    }
}

