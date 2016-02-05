import QtQuick 2.0
import StyleSettings 1.0

ComboBox {
    id: component
    property color color: "white"

    comboButton: Rectangle {
        color: "transparent"
        border.color: component.color
        border.width: 1

        Text {
            text: currentItem
            color: StyleSettings.ternaryTextColor
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    icon: Item {
        Image {
            source: "qrc:/resources/images/arrow.svg"
            fillMode: Image.PreserveAspectFit

            width: parent.width / 2
            height: width

            sourceSize.width: width
            sourceSize.height: height

            anchors.centerIn: parent
        }
    }

    dropDownMenuBackground: Rectangle {
        color: "#272626"
        border.width: 1
        border.color: component.color
    }

    menuItem: Rectangle {
        color: (hovered) ?StyleSettings.primaryColor :"transparent"

        Behavior on color {
            ColorAnimation { duration: 120 }
        }

        Text {
            color: StyleSettings.ternaryTextColor
            text: itemData
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}

