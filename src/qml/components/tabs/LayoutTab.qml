import QtQuick 2.5
import StyleSettings 1.0
import TagOptionsDialog 1.0
import TagMenuSelection 1.0
import TagsContainer 1.0
import TagableDIL 1.0
import InteractiveDialog 1.0
import ConsoleDialog 1.0
import AppStates 1.0
import "../dialogs" as Dialogs
import "../visualization" as Visualization

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

    function objectNameOfTag(pin, tagName) { return tagableDil.objectNameOfTag(pin, tagName) }
    function addMsg(objName, msg, time) { consoleDialog.addMessage(objName, msg, time) }
    function setTagValue(pin, tagType, value) {
        var tag = tagableDil.tag(parseInt(pin), tagType)
        if(tag !== null)
            tag.setValue(value)
    }
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
    function setTagsLock(lock) {
        if(lock) {
            tagsContainer.lock()
            tagOptionsDialog.lock()
            tagableDil.lockTags()
            lockPanel.show()
        }
        else {
            tagsContainer.unlock()
            tagOptionsDialog.unlock()
            tagableDil.unlockTags()
            lockPanel.hide()
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            tagableDil.disselectAll()
        }
    }

    ConsoleDialog {
        id: consoleDialog

        width: tagOptionsDialog.width * 1.2
        titleFrameHeight: 50
        contentFrameHeight: 400

        title: qsTr("Console")
        titleTextColor: "white"
        titleColor: "#1f1f1f"
        titleFont.pixelSize: 20

        contentColor: "#3E3E3E"
        contentFont.pixelSize: 12

        dataColors: ["#00B8FF", "#FF3180", "#09CF84", "orange", "#D3D3D3"]

        margin: contentFont.pixelSize * 1.4
        dropDownsTitleFont.pixelSize: 18
        dropDownsTitleColor: "#303030"
        dropDownsTitleTextColor: "#D3D3D3"
        dropDownsTitleHeight: 40
        dataPanelHeight: 30
        lineColor: "#818181"
        notificationColor: "orange"

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Flickable {
            id: flick

            y: consoleDialog.titleFrameHeight
            width: parent.width
            height: consoleDialog.contentFrameHeight
            boundsBehavior: Flickable.StopAtBounds
            clip: true

            contentWidth: consoleDialog.containerWidth
            contentHeight: consoleDialog.containerHeight
        }

        Rectangle {
            id: scrollBar

            width: 2
            opacity: 0

            color: "white"

            anchors.right: flick.right

            Behavior on opacity {
                NumberAnimation { duration: 400 }
            }
        }

        Component.onCompleted: {
            consoleDialog.setContainerParent(flick.contentItem)
            scrollBar.y = Qt.binding(function() { return flick.visibleArea.yPosition * flick.height + consoleDialog.titleFrameHeight })
            scrollBar.height = Qt.binding(function() { return flick.visibleArea.heightRatio * flick.height })
            scrollBar.opacity = Qt.binding(function() { return flick.visibleArea.heightRatio != 1 })
        }
    }

    Connections {
        target: AppInfo
        onModeChanged: {
            if(AppInfo.mode == AppStates.Running) {
                if(tagOptionsDialog.mode != "None") {
                    var tag = tagableDil.lastSelectedTag()

                    if(tag != null) {
                        tag.options = tagOptionsDialog.dialogOptions()
                        tag.controlState = interactiveDialog.dialogOptions()
                    }
                }

                //tagableDil.disselectAll()
                consoleDialog.clear()
                consoleDialog.portsNames = tagableDil.objectNamesOfConcreteTagTypes(["UTX", "DATW"])
            }

            else {
                tagableDil.restoreNames()
            }
        }
    }

    InteractiveDialog {
        id: interactiveDialog

        property bool showed: false
        property int _y: -height * (!showed)

        dirPath: "settings"
        mode: tagOptionsDialog.mode
        titleColor: "orange"
        panelHeight: 35
        width: 325
        height: fontMetrics.height + 1
        color: "#2f2f2f"
        font.pixelSize: 35
        font.family: "Roboto Light"
        opacity: 0

        anchors.right: tagOptionsDialog.right
        anchors.top: tagOptionsDialog.bottom
        anchors.topMargin: interactiveDialog._y

        Behavior on _y {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
                onRunningChanged: {
                    if(running && interactiveDialog.showed)
                        interactiveDialog.opacity = 1
                    else if(!running && !interactiveDialog.showed)
                        interactiveDialog.opacity = 0
                }
            }
        }

        Component.onCompleted: createDialogComponents()

        onModeChanged: showOrHideInteractiveDialogPart()
        onControlValueChanged: tab.controlValueChanged(value)

        Connections {
            target: AppInfo
            onModeChanged: interactiveDialog.showOrHideInteractiveDialogPart()
        }

        function showOrHideInteractiveDialogPart() {
            if(!interactiveDialog.empty() && AppInfo.mode == AppStates.Running)
                interactiveDialog.showed = true
            else
                interactiveDialog.showed = false
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

    Visualization.LockPanel {
        id: lockPanel

        interactiveMarkColor: tagOptionsDialog.titleColor
        color: "#1c1c1c"

        width: 35
        height: tagOptionsDialog.height + interactiveDialog.showed * interactiveDialog.height
        interactivePartHeight: interactiveDialog.showed * interactiveDialog.height

        anchors.top: tagOptionsDialog.top
        anchors.right: tagOptionsDialog.left
    }
}

