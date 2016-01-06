import QtQuick 2.0
import ComposeableDialog 1.0
import TagMenuSelection 1.0
import TagsContainer 1.0
import TagableDIL 1.0

Item {
    id: tab

    property var tags: [
        ["VDD", "GND"],
        ["GPIO"],
        ["FUN"]
    ]

    MouseArea {
        anchors.fill: parent
        onClicked: tagableDil.disselectAll()
    }

    TagMenuSelection {
        id: tagMenu

        height: 40
        width: 700
        color: "#2f2f2f"
        spacing: 18
        font.family: "Roboto Light"
        font.pixelSize: 22

        tabLabels: [qsTr("POWER"), qsTr("GPIO"), qsTr("FUNCTIONS"), qsTr("UART"), qsTr("SPI"), qsTr("I2C"), qsTr("WATCHERS")]
        tabTextColors: ["#c32026", "#0791cc" , "#f7972b", "#71bf43", "#ec228c", "#b700f9", "#959595"]

        Component.onCompleted: tagMenu.syntheticTabSelect(0)

        onTabSelected: {
            tagsContainer.visibleTags = tab.tags[index]
        }
    }

    TagsContainer {
        id: tagsContainer
        font.family: "Roboto Light"
        font.pixelSize: 25
        spacing: 20
        textColor: "white"
        color: "lightGray"
        tagSize: Qt.size(100, 31)
        height: 50
        visibleTags: tab.tags[0]

        anchors.top: line.bottom

        Component.onCompleted: tagsContainer.createTags()
        onNewObject: tagableDil.registerTag(object)
    }

    // split line
    Rectangle {
        id: line

        color: "#2f2f2f"

        width: parent.width
        height: 4

        anchors.top: tagMenu.bottom
    }

    TagableDIL {
        id: tagableDil

        width: 1400//height * (720. / 420.)
        height: parent.height * 0.8//parent.height

        y: 150

        onSelectedTag: {
            var key
            for(key in tab.tags) {
                if(tab.tags[key].indexOf(tagType) !== -1)
                    break;
            }

            cd.mode = tagType
            cd.setDialogOptions(tagOptions)
            cd.titleColor = tagMenu.tabTextColors[key]
        }

        onDisselectedTag: {
            tag.options = cd.dialogOptions()
        }

        onDisselected: {
            cd.mode = "None"
        }
    }

    ComposeableDialog {
        id: cd

        dirPath: "settings"
        panelHeight: 35
        width: 325
        height: 550
        color: "#2f2f2f"
        font.pixelSize: 35
        font.family: "Roboto Light"

        anchors.right: parent.right
        anchors.top: line.bottom

        Component.onCompleted: {
            createDialogComponents()
        }
    }
}

