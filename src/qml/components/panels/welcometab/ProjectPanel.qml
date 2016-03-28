import QtQuick 2.0
import StyleSettings 1.0
import ClickableText 1.0
import StyledButton 1.0
import "../../controls"

import "../../auxiliary"

Rectangle {
    id: component

    signal newProject()
    signal openProject()

    color: StyleSettings.secondaryColor

    Triangle {
        id: triangle
        z: 1

        y: 20
        width: 23
        height: 59
        color: StyleSettings.tabSelection.color
    }

    Item {
        x: Math.floor(triangle.width * 1.5)
        y: Math.floor(triangle.y + (triangle.height - 40) / 2.)
        height: parent.height - y

        StyledText {
            id: title

            text: qsTr("VirtualIO Creator")
            color: StyleSettings.secondaryTextColor

            font.family: helveticaThin.name
            font.pixelSize: 40
        }

        ClickableText {
            id: newProjectLink

            height: 28
            text: qsTr("New project...")

            font.family: "Roboto Light"
            color: StyleSettings.ternaryTextColor
            showDescription: false
            backgroundColor: "transparent"

            anchors.top: title.bottom
            anchors.topMargin: height / 2

            onClicked: component.newProject()
        }

        ClickableText {
            height: 28
            text: qsTr("Open project...")

            font.family: "Roboto Light"
            color: StyleSettings.ternaryTextColor
            showDescription: false
            backgroundColor: "transparent"

            anchors.top: newProjectLink.bottom
            anchors.topMargin: height / 2

            onClicked: component.openProject()
        }

        // HELP BUTTON
        StyledButton {
            width: 200
            height: 60

            text: qsTr("HELP")
            textColor: StyleSettings.ternaryTextColor
            color: StyleSettings.ternaryTextColor
            borderColor: StyleSettings.ternaryTextColor

            font.family: "Roboto Light"
            font.pixelSize: Math.floor(height / 2.4)

            anchors.bottom: parent.bottom
            anchors.bottomMargin: height
        }
    }
}
