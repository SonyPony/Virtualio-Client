import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import SerialCommunication 1.0

import CloneableTag 1.0
import TagableDIL 1.0
import DropGrid 1.0

import Tab 1.0
import VerticalTabView 1.0

import "qml/components/window" as Windows
import "qml/components/animations" as Animations
import "qml/components/visualization" as Visualization

import "qml/static/responsivity/responsivity.js" as RL

Item {
    id: rootWindow

    visible: true
    //color: "white"

    VerticalTabView {
        id: t
        width: parent.width
        height: parent.height// / 3

        Tab {
            Button {
                anchors.fill: parent
                text: "red"
                onClicked: t.moveToTab(1)
            }
        }

        Tab {
            Button {
                anchors.fill: parent
                text: "blue"
                onClicked: t.moveToTab(0)
            }
        }
    }


    Button {
        width: 50
        height: 50
        text: "CLick"

        onClicked: t.moveToTab(1)
    }

    /*TagableDIL {
        id: f

        width: height * (720. / 420.)
        height: parent.height
    }*/

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

    /*CloneableTag {
       id: cloneTag

       x: 20
       y: 10
       width: height * 80. / 25.
       height: 18 * (f.height / 420.)

       onNewObject: {
           f.registerTag(object)
       }
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
