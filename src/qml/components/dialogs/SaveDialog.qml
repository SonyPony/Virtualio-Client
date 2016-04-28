import QtQuick 2.5
import QtQuick.Dialogs 1.2
import ModalDialog 1.0
import StyleSettings 1.0
import "../controls" as Controls
import StyledButton 1.0

ModalDialog {
    id: dialog

    signal saveProject(string projectName, string projectPath)
    color: "white"

    FileDialog {
        id: folderDialog

        selectFolder: true
        folder: shortcuts.documents

        onAccepted: {
            projectPathEdit.text = folderDialog.folder
        }
    }

    Controls.StyledText {
        text: qsTr("New Project")
        color: StyleSettings.primaryColor

        font.pixelSize: 30
        font.family: helveticaThin.name

        anchors.left: parent.left
        anchors.leftMargin: container.offset
        anchors.top: parent.top
        anchors.topMargin: container.offset / 2
    }

    StyledButton {
        id: saveButton

        height: 22
        width: 80

        text: qsTr("Save")
        textColor: StyleSettings.primaryColor
        borderColor: "black"
        color: "#373a3a"

        font.pixelSize: 14

        anchors.right: cancelButton.left
        anchors.rightMargin: container.offset
        anchors.bottom: cancelButton.bottom

        onClicked: {
            dialog.saveProject(projectNameEdit.text, projectPathEdit.text)
            dialog.hide()
        }
    }

    StyledButton {
        id: chooseButton

        x: container.x + projectPathEdit.x + projectPathEdit.width + container.offset
        y: Math.floor(container.y + projectPathEdit.y)
        height: 22
        width: 100

        text: qsTr("Choose")
        textColor: "#373a3a"
        borderColor: "black"
        color: "#373a3a"

        font.pixelSize: 14

        onClicked: folderDialog.visible = true
    }

    StyledButton {
        id: cancelButton

        height: 22
        width: 80

        text: qsTr("Cancel")
        textColor: "orange"
        borderColor: "black"
        color: "#373a3a"

        font.pixelSize: 14

        anchors.right: parent.right
        anchors.rightMargin: container.offset
        anchors.bottom: parent.bottom
        anchors.bottomMargin: container.offset / 2

        onClicked: dialog.hide()
    }

    Item {
        id: container

        property int offset: 22

        width: parent.width - offset
        height: projectNameEdit.height + projectPathEdit.height + projectPathEdit.anchors.topMargin

        anchors.bottom: parent.bottom
        anchors.bottomMargin: container.offset * 2.2
        anchors.left: parent.left
        anchors.leftMargin: offset

        Controls.StyledText {
            id: projectNameText

            text: qsTr("Project name")

            font.pixelSize: 14

            anchors.verticalCenter: projectNameEdit.verticalCenter
            anchors.left: parent.left
        }

        Controls.StyledText {
            id: projectPathText

            text: qsTr("Project path")

            font.pixelSize: 14

            anchors.verticalCenter: projectPathEdit.verticalCenter
            anchors.left: parent.left
        }

        Controls.LineEdit {
            id: projectNameEdit

            height: 22

            textColor: "#373a3a"
            borderColor: "#373a3a"
            selectionColor: StyleSettings.primaryColor

            anchors.left: projectNameText.right
            anchors.leftMargin: container.offset
            anchors.right: parent.right
            anchors.rightMargin: container.offset
        }

        Controls.LineEdit {
            id: projectPathEdit

            width: projectNameEdit.width - chooseButton.width - container.offset
            height: 22

            textColor: "#373a3a"
            borderColor: "#373a3a"
            selectionColor: StyleSettings.primaryColor

            anchors.top: projectNameEdit.bottom
            anchors.topMargin: container.offset
            anchors.left: projectNameEdit.left
        }
    }
}
