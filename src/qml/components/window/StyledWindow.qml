import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

import "frame" as Frame
import "frame/icons" as Icons

ApplicationWindow {
    id: root

    visible: true
    color: "red"
    flags: Qt.CustomizeWindowHint |
           Qt.FramelessWindowHint |
           Qt.WindowMinimizeButtonHint |
           Qt.Window

    default property alias content: stack.children

    Rectangle {
        id: stack

        color: root.color
        width: root.width
        height: root.height - frame.height
        border.color: frame.buttonsColor

        anchors.bottom: positioner.bottom
    }

    //-----------------POSITIONER------------------
    Item {
        id: positioner
        anchors.fill: parent
    }
    //---------------------------------------------

    ResizeFrameArea {
        window: root
        anchors.fill: parent
    }

    //--------------------FRAME--------------------
    Frame.Frame {
        id: frame

        property color buttonsColor: buttonsBackground

        color: "#EEEEF2"
        height: 25
        window: root
        buttonsBackground: "#EEEEF2"

        minimizeButton: Frame.FrameButton {     //MINIMIZE
            size: frame.height
            color: frame.buttonsBackground
            action: function() { frame.window.visibility = Window.Minimized }

            icon: Icons.MinimizeIcon {}
        }

        maximizeButton: Frame.FrameButton {     //MAXIMIZE
            size: frame.height
            color: frame.buttonsColor
            action: function() {
                frame.window.visibility = (frame.window.visibility == Window.FullScreen) ?Window.Windowed :Window.FullScreen
            }

            icon: Icons.MaximizeIcon {
                frameColor: frame.buttonsBackground
                state: (frame.window.visibility == Window.FullScreen) ?"window" :"maximize"
            }
        }

        closeButton: Frame.FrameButton {        //CLOSE
            size: frame.height
            action: Qt.quit
            color: frame.buttonsColor

            icon: Icons.CloseIcon {}
        }
    }
    //---------------------------------------------
}
