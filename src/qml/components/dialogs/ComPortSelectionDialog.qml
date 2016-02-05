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

    property int timeout: 20000
    property alias model: comboBox.model
    signal portChosen(string portName)

    onHided: {
        timeoutAnimation.stop()
        component.hide()
    }

    color: "#1a1a1a"
    backgroundColor: "black"

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

    Controls.StyledComboBox {
        id: comboBox

        x: height
        y: height
        parent: component.container
        color: StyleSettings.primaryTextColor

        height: 30
        width: 360
    }

    HorizontalTabView {
        id: tabView

        width: parent.width
        height: parent.height - stepProgress.height * 2

        Tab {
            id: comPortSelectionTab

            onShowed: comboBox.parent = component.container

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

                onClicked: {
                    comboBox.parent = comPortSelectionTab
                    comboBox.hideDropDown()
                    timeoutAnimation.start()
                    tabView.moveToTab(1)
                    component.portChosen(comboBox.currentItem)
                }
            }
        }

        Tab {
            Controls.StyledText {
                id: styledText

                text: qsTr("Verifying")

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: loadingAnimation.bottom
            }

            Controls.StyledText {
                text: "..."

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

                onClicked: {
                    tabView.moveToTab(0)
                }
            }

            TimeoutAnimation {
                id: timeoutAnimation

                width: parent.width
                height: 2
                color: StyleSettings.primaryColor
                duration: component.timeout

                anchors.top: parent.top

                onTimeout: tabView.moveToTab(0)
            }
        }
    }
}

