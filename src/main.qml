import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import SerialCommunication 1.0
import DropGrid 1.0

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

import "qml/static/responsivity/responsivity.js" as RL

import "qml/components/controls" as Controls

Rectangle {
    id: rootWindow

    color: "white"
    visible: true
    //width: 1000
    //height: 500

    //color: "white"
    property font defaultFont: __text.font
    Text { id: __text; visible: false }

    MouseArea {
        id: rootMouseArea

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

            /*ScrollBar {
                x: 300
                y: 50
                height: 400
                width: 7
                color: "gray"
                backgroundColor: "orange"
                ratio: 1.5
                orientation: Qt.Vertical
            }

            StyledButton {
                y: 200
                height: 50
                width: 200
                color: "red"
                textColor: "white"

                font.family: helveticaThin.name
                font.pixelSize: height / 2

                onClicked: {
                    t.moveToTab(1)
                }
            }

            Controls.LineEdit {
                text: "dddd"
                x: 20
                y: 20
                textColor: "white"
                placeholderText: "Foo"
                placeHolderTextColor: "lightGray"
                borderColor: "red"
                selectionColor: "black"

                width: 200
                height: 20
            }*/

            /*Rectangle {
                id: image
                width: parent.width - recent.width
                height: 535
                anchors.bottom: parent.bottom
                color: "#f5f5f5"

                Text {
                    id: ecosystem
                    text: "ECOSYSTEM"
                    color: "#007ACC"//"#f0f0f0"

                    font.family: helveticaThin.name
                    font.pixelSize: 45

                    anchors.left: schematic.right
                    anchors.leftMargin: 45
                    anchors.top: schematic.top
                }

                Text {
                    id: label
                    text: "Use Virtualis to test your microcontroller"
                    color: "gray"

                    font.family: helveticaThin.name
                    font.pixelSize: 25

                    anchors.left: schematic.right
                    anchors.leftMargin: 45
                    anchors.top: ecosystem.bottom
                }

                Text {
                    id: textcontent

                    text: "Virtualis is powerful tool, which helps you to test devices such as ADC with differents interfaces, your microcontrollers or any other chips. " +
                          "With Virtualis you can simulate UART, I2C, SPI, digital I/O and read analog."

                    color: "gray"
                    font.family: helveticaThin.name
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                    width: rootWindow.width - schematic.width - recent.width - menu.width - 150

                    anchors.left: schematic.right
                    anchors.leftMargin: 45
                    anchors.top: label.bottom
                    anchors.topMargin: 25
                }

                Rectangle {
                    anchors.left: textcontent.left
                    anchors.top: textcontent.bottom
                    anchors.topMargin: 45

                    color: "transparent"
                    border.color: "#007ACC"
                    height: 60
                    width: 250

                    Text {
                        text: "GET STARTED"
                        color: parent.border.color

                        font.family: helveticaThin.name
                        font.pixelSize: 25

                        anchors.centerIn: parent
                    }
                }

                Image {
                    id: schematic

                    source: "qrc:/resources/images/schematic.svg"

                    x: 75
                    fillMode: Image.PreserveAspectFit
                    width: 2 * height
                    height: 400

                    sourceSize.width: width
                    sourceSize.height: height

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 35

                    MouseArea {
                        anchors.fill: parent
                        onClicked: t.moveToTab(1)
                    }
                }
            }

            Rectangle {
                id: recent

                width: 350
                height: parent.height
                color: "#4b4b4b"//"#f0f0f0"

                anchors.right: parent.right

                Rectangle {
                    color: "orange"
                    width: parent.width - 25
                    anchors.top: recentText.bottom
                }

                Text {
                    id: recentText

                    color: "#009cde"//"#007ACC"
                    text: "Recent projects"

                    x: 15
                    y: 15

                    font.family: helveticaThin.name
                    font.pixelSize: 45
                }
            }*/
        }

        Tab {
            Visualization.ResizeableGraph {
                y: 150

                    width: parent.width- 40
                    height: 400

                }
            //Tabs.TagTab {}
        }

        Tab {
            Tabs.TagTab {}
        }
    }

    /*DropGrid {
        id: lGrid
        width: 300
        height: 406 + 1*13
        columns: 4
        objectsAlign: Qt.AlignLeft
        rows: dGrid.rows
        y: dGrid.y
        x: 370
    }

    DropGrid {
        id: dGrid

           width: 300
           height: 406 + 1*13
           columns: 4
           objectsAlign: Qt.AlignRight
           rows: 21
           y: dil.y - 7
           x: 30

    }

    Image {
        id: dil
        source: "qrc:/resources/images/DIL.svg"

        width: 154
        height: 406

        sourceSize: Qt.size(width, height)

        anchors.centerIn: parent
    }*/


    /*Visualization.ResizeableGraph {
        y: 200
        width: 1000
        height: 150

    }*/

    /*SerialCommunication {
        portIdentifier: "stlink"
        onMessage: {

        }

        Component.onCompleted: tryConnect()
        onConnectedChanged: console.log("Connection: ", connected)
        onError: console.log(arg)
    }

    Windows.StackBar {
        id: stackBar

        color: "#007ACC"
        height: 20
        width: parent.width

        anchors.bottom: parent.bottom
    }

    Windows.SubWindow {
        id: ff
        width: 100
        height: 100
        x: 300
        tabName: "FooBar"

        Component.onCompleted: stackBar.registerWindow(ff)
    }
    */
}
//}
