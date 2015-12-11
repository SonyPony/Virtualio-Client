import QtQuick 2.0
import StyledButton 1.0
import StyleSettings 1.0
import "../../controls" as Controls

Rectangle {
    color: StyleSettings.aboutPanel.backgroundColor

    //----------------SCHEMATIC----------------
    Image {
        id: schematic

        source: StyleSettings.aboutPanel.schematicPath
        fillMode: Image.PreserveAspectFit
        smooth: true

        width: height * (55. / 34.)
        height: parent.height * 0.9

        sourceSize: Qt.size(1100, 640)

        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.verticalCenter: parent.verticalCenter
    }
    //-----------------------------------------

    //---------------DESCRIPTION---------------
    // LABEL
    Controls.StyledText {
        id: ecosystem

        text: qsTr("ECOSYSTEM")
        color: StyleSettings.primaryColor

        font.pixelSize: 45

        anchors.left: schematic.right
        anchors.leftMargin: 15
        anchors.top: schematic.top
    }
    // SUMMARY
    Controls.StyledText {
        id: summary

        text: qsTr("Use VirtualIO to test your microcontroller")

        anchors.left: ecosystem.left
        anchors.top: ecosystem.bottom
    }
    // DESCRIPTION
    Controls.StyledText {
        id: description

        text: "VirtualIO is powerful tool, which helps you to test devices such " +
              "as ADC with differents interfaces, your microcontrollers or any other chips. " +
              "With VirtualIO you can simulate UART, I2C, SPI, digital I/O and read analog."
        width: parent.width - schematic.width - ecosystem.anchors.leftMargin - schematic.anchors.leftMargin - 35
        font.pixelSize: 20

        anchors.left: summary.left
        anchors.topMargin: 25
        anchors.top: summary.bottom
    }
    //-----------------------------------------

    // GET STARTED BUTTON
    StyledButton {
        x: Math.floor(description.x)
        width: 240
        height: 60

        text: qsTr("GET STARTED")
        textColor: StyleSettings.primaryColor
        color: StyleSettings.primaryColor

        font.family: helveticaThin.name
        font.pixelSize: Math.floor(height / 2.7)

        anchors.topMargin: height
        anchors.top: description.bottom
    }
}

