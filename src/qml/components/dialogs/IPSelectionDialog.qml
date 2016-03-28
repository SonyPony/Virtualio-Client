import QtQuick 2.0
import HorizontalTabView 1.0
import Tab 1.0
import StyleSettings 1.0
import StepProgress 1.0
import VerticalTabView 1.0
import StyledButton 1.0
import TimeoutAnimation 1.0
import ModalDialog 1.0

import "../animations" as Animations
import "../controls" as Controls

ModalDialog {
    id: component

    property int timeoutTime: 20000
    signal ipEntered(string ip)
    signal timeout()

    onHided: {
        timeoutAnimation.stop()
        component.hide()
    }

    color: "#1a1a1a"
    backgroundColor: "black"

    function moveToLoadingTab() {
        timeoutAnimation.start()
        tabView.moveToTab(1)
        component.ipEntered(lineEdit.text)
    }

    function moveToEntryTab() {
        component.timeout()
        tabView.moveToTab(0)
    }

    StepProgress {
        id: stepProgress

        width: 30
        height: 8

        color: "white"
        secondColor: "gray"
        currentStep: tabView.currentTab
        stepsCount: tabView.tabsCount()

        anchors.bottom: parent.bottom
        anchors.bottomMargin: height
        anchors.horizontalCenter: parent.horizontalCenter
    }

    HorizontalTabView {
        id: tabView

        width: parent.width
        height: parent.height - stepProgress.height * 2

        Tab {
            id: ipSelectionTab

            Controls.LineEdit {
                id: lineEdit

                x: height
                y: height
                height: 30
                width: 250

                placeholderText: qsTr("IP address")
                validator: RegExpValidator { regExp: /\d?\d?\d\.\d?\d?\d\.\d?\d?\d\.\d?\d?\d/ }

                textColor: StyleSettings.ternaryTextColor
                borderColor: StyleSettings.ternaryTextColor
                selectionColor: StyleSettings.primaryColor
                placeHolderTextColor: StyleSettings.primaryTextColor

                onAccepted: moveToLoadingTab()
            }

            StyledButton {
                width: 70
                height: 30

                text: qsTr("Next")
                textColor: StyleSettings.primaryTextColor
                color: textColor
                borderColor: textColor

                font.family: root.defaultFont
                font.pixelSize: Math.floor(height / 2.4)

                anchors.right: parent.right
                anchors.rightMargin: height / 2.
                anchors.bottom: parent.bottom

                onClicked: moveToLoadingTab()
            }
        }

        Tab {
            Controls.StyledText {
                id: styledText

                text: qsTr("Verifying")

                font.family: helveticaThin.name

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: loadingAnimation.bottom
            }

            Controls.StyledText {
                text: "..."

                font.family: helveticaThin.name

                anchors.left: styledText.right
                anchors.top: styledText.top
            }

            Animations.LoadingAnimation {
                id: loadingAnimation

                width: height
                height: parent.height - anchors.topMargin * 2. - styledText.height
                lineWidth: 1
                outerColor: "gray"
                innerColor: "#007ACC"

                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
            }

            StyledButton {
                width: 70
                height: 30

                text: qsTr("Back")
                textColor: StyleSettings.primaryTextColor
                color: textColor
                borderColor: textColor

                font.family: root.defaultFont
                font.pixelSize: Math.floor(height / 2.4)

                anchors.right: parent.right
                anchors.rightMargin: height / 2.
                anchors.bottom: parent.bottom

                onClicked: moveToEntryTab()
            }

            TimeoutAnimation {
                id: timeoutAnimation

                width: parent.width
                height: 2
                color: StyleSettings.primaryColor
                duration: component.timeoutTime

                anchors.top: parent.top

                onTimeout: moveToEntryTab()
            }
        }
    }
}

