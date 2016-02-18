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
        id: projectPanel

        width: height
        height: component.height - aboutPanel.height
    }

    RecentProjectsView {
        color: "#434647"
        titleColor: StyleSettings.secondaryTextColor

        width: parent.width - aboutPanel.width
        height: parent.height

        font.family: helveticaThin.name
        font.pixelSize: 40

        anchors.right: parent.right
    }
}

