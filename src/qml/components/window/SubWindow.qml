import QtQuick 2.0
import "frame" as Frame
import "frame/icons" as Icons

import "../../logic/responsivity/responsivity.js" as RL

Item {
    id: root

    property size minimizedSize: Qt.size(tabText.width + 15, Math.max(frame.height, tabText.height))
    property point minimizedPos: Qt.point(100, 100)
    property size actualSize
    property point actualPos
    property color tabColor: "#007ACC"
    property string tabName: "Default"

    default property alias content: stack.children
    signal minimizeAnimation
    signal windowAnimation

    state: "windowed"
    clip: true

    onStateChanged: {
        if(root.state == "windowed")
            windowAnimation()
        else
            minimizeAnimation()
    }

    //---------MINIMIZATION FUNCTION STUFF---------
    Component.onCompleted: {
        actualPos = Qt.point(x, y)
        actualSize = Qt.size(width, height)
    }
    onWidthChanged: if(root.state == "windowed")
                        actualSize = Qt.size(width, height)

    onHeightChanged: if(root.state == "windowed")
                         actualSize = Qt.size(width, height)

    onXChanged: if(root.state == "windowed")
                    actualPos = Qt.point(root.x, root.y)

    onYChanged: if(root.state == "windowed")
                    actualPos = Qt.point(root.x, root.y)

    onWindowAnimation: SequentialAnimation {
        ParallelAnimation {
            NumberAnimation { target: root; property: "x"; to: actualPos.x; easing.type: Easing.InOutQuad; duration: 500 }
            NumberAnimation { target: root; property: "y"; to: actualPos.y; easing.type: Easing.InOutQuad; duration: 500 }
        }

        NumberAnimation { target: root; property: "width"; to: actualSize.width; easing.type: Easing.InOutQuad; duration: 500 }
        NumberAnimation { target: root; property: "height"; to: actualSize.height; easing.type: Easing.InOutQuad; duration: 500 }
        ScriptAction {
            script: {
                root.x = Qt.binding(function() { return this.actualPos.x })
                root.y = Qt.binding(function() { return this.actualPos.y })
            }
        }
    }

    onMinimizeAnimation: SequentialAnimation {
        NumberAnimation { target: root; property: "height"; to: minimizedSize.height; easing.type: Easing.InOutQuad; duration: 500 }
        NumberAnimation { target: root; property: "width"; to: minimizedSize.width; easing.type: Easing.InOutQuad; duration: 500 }
        ParallelAnimation {
            NumberAnimation { target: root; property: "x"; to: minimizedPos.x; easing.type: Easing.InOutQuad; duration: 500 }
            NumberAnimation { target: root; property: "y"; to: minimizedPos.y; easing.type: Easing.InOutQuad; duration: 500 }
        }
        ScriptAction {
            script: {
                root.x = Qt.binding(function() { return this.minimizedPos.x })
                root.y = Qt.binding(function() { return this.minimizedPos.y })
            }
        }
    }
    //---------------------------------------------

    //-------------MINIMIZED SUBWINDOW-------------
    Rectangle {
        z: 2
        color: root.tabColor
        opacity: root.state == "minimized"

        width: root.minimizedSize.width
        height: root.minimizedSize.height

        Behavior on opacity {
            NumberAnimation { duration: 1000 }
        }

        Text {
            id: tabText

            text: root.tabName
            color: "white"

            font.family: "Trebuchet MS"
            font.pixelSize: 15
            anchors.centerIn: parent
        }

        MouseArea {
            enabled: root.state == "minimized"
            anchors.fill: parent
            onClicked: root.state = "windowed"
        }
    }
    //---------------------------------------------

    //--------------------FRAME--------------------
    Frame.Frame {
        id: frame

        property color buttonsColor: "#007ACC"

        color: "transparent"
        height: 20
        window: root
        autoHideButtons: true

        minimizeButton: Frame.FrameButton {     //MINIMIZE
            size: frame.height
            color: frame.buttonsColor
            action: function() { root.state = "minimized" }

            icon: Icons.MinimizeIcon { iconColor: "white" }
        }

        closeButton: Frame.FrameButton {        //CLOSE
            size: frame.height
            action: function() { root.visible = false }
            color: frame.buttonsColor

            icon: Icons.CloseIcon { iconColor: "white" }
        }
    }
    //---------------------------------------------

    //------------WINDOW FUNCTION STUFF------------
    Rectangle {
        id: stack

        width: root.width
        height: root.height - frame.height
        clip: true

        anchors.bottom: root.bottom
        border.color: "lightGray"

        ResizeFrameArea {
            active: root.state == "windowed"
            minimalSize: Qt.size(0, 0)
            window: root
            anchors.fill: parent
        }
    }
    //---------------------------------------------

}
