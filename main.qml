import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import SerialCommunication 1.0

import CloneableTag 1.0
import CloneTag 1.0

import "components/window" as Windows
import "components/animations" as Animations
import "components/visualization" as Visualization

Windows.StyledWindow {
    id: rootWindow

    width: 640
    height: 480
    visible: true
    color: "white"

    CloneableTag {
        width: 10
        height: 10
    }

    Visualization.ResizeableGraph {
        y: 200
        width: 1000
        height: 150

    }

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
