import QtQuick 2.0
import "../code" as Code
import Tab 1.0
import StyleSettings 1.0

Tab {
    Code.CodeEditor {
        width: parent.width
        height: parent.height - panel.height
    }

    Rectangle {
        id: panel

        width: parent.width
        height: 25
        color: StyleSettings.secondaryColor

        anchors.bottom: parent.bottom
    }
}

