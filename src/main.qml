import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import SerialCommunication 1.0
import DropGrid 1.0

import ComposeableDialog 1.0

import StyledButton 1.0
import Tab 1.0
import VerticalTabView 1.0
import MainTabsSelection 1.0
import ScrollBar 1.0
import NonInteractiveScrollBar 1.0

import StyleSettings 1.0
import ClickableText 1.0

import "qml/components/window" as Windows
import "qml/components/animations" as Animations
import "qml/components/visualization" as Visualization
import "qml/components/tabs" as Tabs
import "qml/components/panels/composeable" as Panels

import "qml/static/responsivity/responsivity.js" as RL

import "qml/components/controls" as Controls

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

    FontLoader {
        id: helveticaThin
        source: "qrc:/resources/fonts/HelveticaNeue-Thin.otf"
    }

    FontLoader {
        source: "qrc:/resources/fonts/Roboto-Light.ttf"
    }

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

        onTabSelected: t.moveToTab(index)
    }

    VerticalTabView {
        id: t
        x: menu.width
        width: parent.width - menu.width
        height: parent.height// / 3

        Tab {
            Tabs.WelcomeTab {

            }
        }

        Tab {
            Tabs.LayoutTab {
                anchors.fill: parent
            }
        }

        Tabs.ScriptTab {
        }

        Tab {
            Visualization.ResizeableGraph {
                y: 150

                    width: parent.width- 40
                    height: 400

                }
        }

        Tab {

        }
    }

    /*SerialCommunication {
        portIdentifier: "stlink"
        onMessage: {

        }

        Component.onCompleted: tryConnect()
        onConnectedChanged: console.log("Connection: ", connected)
        onError: console.log(arg)
    }*/

}

