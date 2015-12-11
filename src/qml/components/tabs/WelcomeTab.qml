import QtQuick 2.0
import "../panels/welcometab" as Panels

Item {
    id: component
    anchors.fill: parent

    Panels.AboutPanel {
        id: aboutPanel

        width: parent.width * 0.8
        height: parent.height * 0.55

        anchors.bottom: parent.bottom
    }

    Panels.ProjectPanel {
        width: height
        height: component.height - aboutPanel.height
    }
}

