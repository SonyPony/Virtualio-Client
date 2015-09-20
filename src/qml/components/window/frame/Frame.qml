import QtQuick 2.0
import QtQuick.Window 2.2
import "icons" as Icons

Rectangle {
    id: frame

    property var window
    property color buttonsBackground: "#007ACC"
    property Component closeButton
    property Component minimizeButton
    property Component maximizeButton
    property bool autoHideButtons: false

    width: parent.width
    clip: true

    //------------------CLICK RESIZE---------------
    MouseArea {
        property var clickPos

        hoverEnabled: autoHideButtons
        anchors.fill: parent

        onDoubleClicked: frame.window.visibility = (frame.window.visibility === Window.FullScreen) ?Window.Windowed :Window.FullScreen
        onPressed: clickPos = Qt.point(mouse.x,mouse.y)
        onPositionChanged: {
            if(pressedButtons) {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

                frame.window.x += delta.x;
                frame.window.y += delta.y;
            }
        }
        onEntered: {
            if(autoHideButtons)
                buttonsPanel.y = 0
        }
        onExited: {
            if(autoHideButtons)
                buttonsPanel.y = buttonsPanel.height
        }
    }
    //---------------------------------------------

    //------------------BUTTONS--------------------
    Rectangle {
        id: buttonsPanel

        y: (autoHideButtons) ?height :0
        width: buttons.width + 20
        height: frame.height
        color: frame.buttonsBackground

        anchors.right: parent.right

        Behavior on y {
            NumberAnimation { easing.type: Easing.InOutQuad; duration: 200}
        }

        Row {
            id: buttons
            spacing: 5
            anchors.centerIn: parent

            Loader {
                sourceComponent: frame.minimizeButton
            }

            Loader {
                sourceComponent: frame.maximizeButton
            }

            Loader {
                sourceComponent: frame.closeButton
            }

        }
    }
    //---------------------------------------------
}

