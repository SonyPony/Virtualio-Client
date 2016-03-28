import QtQuick 2.0
import ModulesConnectionView 1.0
import StyleSettings 1.0
import ModuleState 1.0
import "../../auxiliary"
import "../../controls"

Rectangle {
    color: "transparent"

    function setModuleState(moduleName, state) { connectionView.setModuleState(moduleName, state) }

    Triangle {
        id: triangle
        z: 1

        y: 20
        width: 23
        height: 59
        color: StyleSettings.secondaryColor
    }

    StyledText {
        id: title

        x: Math.floor(triangle.width * 1.5)
        y: Math.floor(triangle.y + (triangle.height - 40) / 2.)

        text: qsTr("Status")
        color: StyleSettings.ternaryColor

        font.family: helveticaThin.name
        font.pixelSize: 40
    }

    ModulesConnectionView {
        id: connectionView

        width: parent.width - anchors.leftMargin
        height: parent.height / 1.5

        activeColor: StyleSettings.primaryColor
        nameColor: StyleSettings.ternaryColor
        inactiveColor: StyleSettings.secondaryColor
        connectionTablePos: 400
        modulesNames: [
            "VIO board",
            "Power management",
            "Digital IO",
            "UART Communication",
            "SPI Communitation",
            "I2C Communication",
            "Digital wathers",
            "Analog watchers"
        ]

        font.family: "Roboto Light"
        font.pixelSize: 23

        anchors.left: title.left
        anchors.leftMargin: triangle.width / 2
        anchors.top: title.bottom
    }
}

