import QtQuick 2.0
import "../panels/welcometab" as Panels
import ModulesConnectionView 1.0
import StyleSettings 1.0
import RecentProjectsView 1.0

Item {
    id: component

    signal newProject()
    signal openProject()
    function addProject(project) { recentProjects.addProjectPath(project) }
    function setModuleState(moduleName, state) { modulesView.setModuleState(moduleName, state) }

    anchors.fill: parent

    Panels.ModulesConnectionPanel {
        id: modulesView

        width: aboutPanel.width - projectPanel.width
        height: projectPanel.height

        anchors.left: projectPanel.right
    }

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

        onNewProject: component.newProject()
        onOpenProject: component.openProject()
    }

    RecentProjectsView {
        id: recentProjects

        color: "#434647"
        titleColor: StyleSettings.secondaryTextColor

        width: parent.width - aboutPanel.width
        height: parent.height

        font.family: helveticaThin.name
        font.pixelSize: 40

        linksFont.family: "Roboto Light"
        linksFont.pixelSize: 16

        anchors.right: parent.right

        Component.onCompleted: loadRecentProjects()
        onProjectSelected: ProjectActions.loadProjectFile(path)
    }
}

