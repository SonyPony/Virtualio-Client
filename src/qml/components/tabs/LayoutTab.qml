import QtQuick 2.5
import TagOptionsDialog 1.0
import TagMenuSelection 1.0
import TagsContainer 1.0
import TagableDIL 1.0
import InteractiveDialog 1.0

Item {
    id: tab

    readonly property var tags: [
        ["VDD", "GND"],
        ["GPO"],
        ["FUN"],
        ["UTX"],
        [],
        [],
        ["FUNW", "DATW"]
    ]

    signal controlValueChanged(var value)

    function setTagValue(pin, tagType, value) { tagableDil.tag(parseInt(pin), tagType).setValue(value) }
    function selectedTagInfo() { return tagableDil.selectedTagInfo() }
    function tagsFunction() { return tagableDil.tagsFunction() }
    function tagsLayout() { return tagableDil.tags() }
    function clearTags() { tagableDil.clear() }
    function createTags(tags) {
        for(var key in tags) {
            var tag = tags[key]
            tagsContainer.syntheticNewTag(
                tag["name"],
                tagableDil.dropPosition(parseInt(tag["pin"])),
                tag["options"]
            )
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            //tagableDil.tag(2, "GPO").setValue("ST: 1")
            tagableDil.disselectAll()
        }
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

        width: tab.width - tagOptionsDialog.width
        height: parent.height * 0.8

        y: 150

        onSelectedTag: {
            var key
            for(key in tab.tags) {
                if(tab.tags[key].indexOf(tagType) !== -1)
                    break;
            }

            tagOptionsDialog.mode = tagType
            tagOptionsDialog.setDialogOptions(tag.options)
            interactiveDialog.setDialogOptions(tag.controlState)
            tagOptionsDialog.titleColor = tagMenu.tabTextColors[key]
        }

        onDisselectedTag: {
            tag.options = tagOptionsDialog.dialogOptions()
            tag.controlState = interactiveDialog.dialogOptions()
        }

        onDisselected: {
            tagOptionsDialog.mode = "None"
        }
    }

    FontMetrics {
        id: fontMetrics
        font: tagOptionsDialog.font
    }

    TagOptionsDialog {
        id: tagOptionsDialog

        dirPath: "settings"
        panelHeight: 35
        width: 325
        height: fontMetrics.height + 1
        color: "#2f2f2f"
        font.pixelSize: 35
        font.family: "Roboto Light"

        anchors.right: parent.right
        anchors.top: line.bottom

        Component.onCompleted: {
            createDialogComponents()
        }
    }

    InteractiveDialog {
        id: interactiveDialog

        dirPath: "settings"
        mode: tagOptionsDialog.mode
        titleColor: tagOptionsDialog.titleColor
        panelHeight: 35
        width: 325
        height: fontMetrics.height + 1
        color: "#2f2f2f"
        font.pixelSize: 35
        font.family: "Roboto Light"

        anchors.right: parent.right
        anchors.top: tagOptionsDialog.bottom

        Component.onCompleted: {
            createDialogComponents()
        }

        onControlValueChanged: {
            tab.controlValueChanged(value)
        }
    }
}

