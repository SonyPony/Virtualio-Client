import QtQuick 2.0
import TagMenuSelection 1.0

Item {
    id: tab

    TagMenuSelection {
        id: tagMenu

        height: 40
        width: 700
        color: "#2f2f2f"
        spacing: 18
        font.family: "Roboto Light"
        font.pixelSize: 22

        tabLabels: [qsTr("POWER"), qsTr("GPIO"), qsTr("FUNCTIONS"), qsTr("UART"), qsTr("SPI"), qsTr("I2C"), qsTr("WATCHERS")]
        tabTextColors: ["#c32026", "#0791cc" , "#f7972b", "#71bf43", "#ec228c", "#8b278b", "#959595"]

        onTabSelected: console.log(index)
    }

    // split line
    Rectangle {
        color: "#2f2f2f"

        width: parent.width
        height: 4

        anchors.top: tagMenu.bottom
    }
}

