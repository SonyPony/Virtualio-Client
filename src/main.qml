import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import Tab 1.0
import VerticalTabView 1.0
import MainTabsSelection 1.0

import StyleSettings 1.0
import IconButton 1.0
import MessageDialog 1.0
import GraphsWidget 1.0
import MessageManager 1.0
import WebsocketClient 1.0
import FileStream 1.0

import "qml/components/animations" as Animations
import "qml/components/visualization" as Visualization
import "qml/components/tabs" as Tabs
import "qml/components/panels/composeable" as Panels
import "qml/components/dialogs" as Dialogs

import "qml/static/responsivity/responsivity.js" as RL

import "qml/components/controls" as Controls
import "qml/static/actions" as Actions

Rectangle {
    id: root

    color: "white"
    visible: true
    //width: 1000
    //height: 500

    property font defaultFont: __text.font
    Text { id: __text; visible: false }

    MouseArea {
        id: rootMouseArea
        objectName: "rootMouseArea"

        propagateComposedEvents: true
        z: 6
        enabled: false
        anchors.fill: root
        onClicked: mouse.accepted = false
    }

    FileStream {
        id: lastIP
        source: "lastip.txt"

        Component.onCompleted: {
            var lastUsedIP = lastIP.read()
            if(lastUsedIP != "")
                ipDialog.setText(lastUsedIP)
        }
    }

    WebsocketClient {
        id: websocketClient
    }

    FileDialog {
        id: fileDialog

        selectFolder: true
        folder: shortcuts.documents
    }

    FontLoader {
        id: helveticaThin
        source: "qrc:/resources/fonts/HelveticaNeue-Thin.otf"
    }

    FontLoader {
        source: "qrc:/resources/fonts/Roboto-Light.ttf"
    }

    Actions.ActionBindings {}

    MainTabsSelection {
        id: menu

        width: 75
        height: parent.height

        iconsPaths: [
            ":/resources/images/welcomeIcon.svg",
            ":/resources/images/layoutIcon.svg",
            ":/resources/images/luaIcon.svg",
            ":/resources/images/analyzeIcon.svg",
            ":/resources/images/helpIcon.svg"
        ]
        tabLabels: ["Welcome", "Layout", "Scripts", "Analyze", "Help"]
        spacing: 10
        textColor: "white"
        font.family: "Roboto Light"
        font.pixelSize: 14
        iconSize: 45

        color: "#2f2f2f"

        onTabSelected: {
            selectionPointer.y = (selectionPointer.height + 10 + 5) * index + 15
            tabs.moveToTab(index)
        }

        IconButton {
            id: playButton

            width: parent.width * 0.4
            height: width
            iconPath: ":/resources/images/playIcon.svg"
            disabledIconPath: ":/resources/images/disabledPlayIcon.svg"
            enabled: false//(tabs.currentTab === 1 || tabs.currentTab === 2)

            anchors.bottom: stopButton.top
            anchors.bottomMargin: height / 2
            anchors.horizontalCenter: parent.horizontalCenter
        }

        IconButton {
            id: stopButton

            width: playButton.width * 0.9
            height: width
            iconPath: ":/resources/images/stopIcon.svg"
            disabledIconPath: ":/resources/images/disabledStopIcon.svg"
            enabled: false

            anchors.bottom: parent.bottom
            anchors.bottomMargin: height
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
            }
        }

        Rectangle {
            id: selectionPointer
            y: 15
            color: StyleSettings.primaryColor
            width: 2
            height: menu.width - 5

            Behavior on y {
                NumberAnimation { duration: 400; easing.type: Easing.InOutQuad }
            }
        }
    }

    MessageManager {
        id: messageManager
    }

    MessageDialog {
        id: messageDialog

        title: qsTr("Warning")
        z: 10
        dialogBaseSize.height: 200

        color: "#f2f2f2"

        buttonColor: "#2f2f2f"
        buttonFont.family: root.defaultFont.name
        buttonFont.pixelSize: 15

        titleFont.family: "Roboto Light"
        titleColor: "orange"
        titleFont.pixelSize: 40

        messageFont.family: "Roboto Light"
        messageFont.pixelSize: 20

        anchors.fill: parent

        function error(msg) {
            messageDialog.message = msg
            messageDialog.focus = true
            messageDialog.show()
        }
    }

    Dialogs.IPSelectionDialog {
        id: ipDialog

        z: 10
        dialogBaseSize.width: root.width * 0.2
        dialogBaseSize.height: root.height * 0.15

        anchors.fill: parent

        onIpEntered: console.log(ip)
        // DELETE!!!!---------------------------------
        //Component.onCompleted: hide()
    }

    VerticalTabView {
        id: tabs

        x: menu.width
        width: parent.width - menu.width
        height: parent.height// / 3

        Tab {
            Tabs.WelcomeTab {
                id: welcomeTab
            }
        }

        Tab {
            Tabs.LayoutTab {
                id: layoutTab
                anchors.fill: parent
            }
        }

        Tabs.ScriptTab {
            id: scriptTab
        }

        Tab {
            GraphsWidget {
                id: gw

                width: parent.width
                height: 350

                Component.onCompleted: {
                    var data = {
                        "Volt": {
                            "dataY": [0, 30, 0, 30],
                            "dataX": [0, 20, 40, 60]
                        },

                        "Something": {
                            "dataY": [0, 30, 50, 30],
                            "dataX": [0, 20, 40, 60]
                        }
                    }
                    gw.setGraphsDatas(data)
                }
            }
        }

        Tab {
        }
    }
}

