import QtQuick 2.0
import GraphAxis 1.0
import GraphContent 1.0
import GraphView 1.0
import NonInteractiveScrollBar 1.0
import "../controls" as Controls

Item {
    id: component

    property alias dataX: graphContent.dataX
    property alias dataY: graphContent.dataY
    property int contentHeight
    property alias viewHeight: graphView.height
    property alias label: label.text

    property QtObject verticalAxis: QtObject {
        objectName: "verticalAxis"
        property alias interval: __verticalAxis.values
        property alias labelsCount: __verticalAxis.valuesCount
    }

    property QtObject horizontalAxis: QtObject {
        objectName: "horizontalAxis"
        property alias interval: __horizontalAxis.values
        property alias labelsCount: __horizontalAxis.valuesCount
    }

    height: contentHeight + viewHeight

    Item {
        id: verticalFlick

        width: __verticalAxis.width
        height: component.contentHeight - __horizontalAxis.offset
        clip: true

        anchors.bottom: component.bottom
        anchors.bottomMargin: __horizontalAxis.offset

        GraphAxis {
            id: __verticalAxis

            y: -contentFlick.contentY
            width: component.width
            height: parent.height
            color: Qt.rgba(0.95, 0.95, 0.95, 1)

            font: "Helvetica"
            textColor: "gray"
            fontSize: 10
            lineWidth: 1

            textMode: GraphAxis.ExcludeFirstAndLast
            values: Core.interval(0, 60)
            valuesCount:  4
            enabledDirections: GraphAxis.Vertical

            Component.onCompleted: __verticalAxis.ratio =  1
        }
    }

    Item {
        id: horizontalFlick

        x: __verticalAxis.offset + verticalFlick.x
        y: component.viewHeight
        width: parent.width - __verticalAxis.offset
        height: __horizontalAxis.height
        clip: true

        GraphAxis {
            id: __horizontalAxis

            x: -contentFlick.contentX
            width: component.width - __verticalAxis.offset
            height: component.contentHeight

            color: Qt.rgba(0.95, 0.95, 0.95, 1)
            font: "Helvetica"
            textColor: "lightGray"
            fontSize: 10
            lineWidth: 1

            textMode: GraphAxis.ExcludeFirstAndLast
            gridMode: GraphAxis.ExcludeFirstAndLast
            values: Core.interval(0, 60)
            valuesCount: 10
            enabledDirections: GraphAxis.Horizontal
            Component.onCompleted: __horizontalAxis.ratio =  1
        }
    }

    Flickable {
        id: contentFlick

        x: __verticalAxis.offset
        y: component.viewHeight
        width: horizontalFlick.width
        height: verticalFlick.height
        contentWidth: graphContent.width
        contentHeight: graphContent.height

        clip: true
        boundsBehavior: Flickable.StopAtBounds

        GraphContent {
            id: graphContent

            color: "#45C8DC"
            width: __horizontalAxis.width
            height: 300

            lineWidth: 1
            squareLineColor: "#373a3a"

            dataY: [10, 20, 30, 0, 60]
            dataX: [10, 20, 40 , 50, 60]
            verticalAxis: __verticalAxis
            horizontalAxis: __horizontalAxis
        }
    }

    Controls.StyledText {
        id: label

        font.family: "Helvetica Neue"
        anchors.top: contentFlick.top
        anchors.left: contentFlick.left
    }

    Item {
        width: contentFlick.width
        height: contentFlick.height

        anchors.left: contentFlick.left
        anchors.bottom: contentFlick.bottom

        NonInteractiveScrollBar {
            position: parent.width * contentFlick.visibleArea.xPosition
            height: 2
            width: contentFlick.visibleArea.widthRatio * parent.width
            active: ((__horizontalAxis.ratio > 1) && contentFlick.movingHorizontally)

            orientation: Qt.Horizontal
            color: "#3a3a3a"

            anchors.top: parent.bottom
        }

        NonInteractiveScrollBar {
            position: parent.height * contentFlick.visibleArea.yPosition
            width: 2
            height: parent.height * contentFlick.visibleArea.heightRatio
            active: (__verticalAxis.ratio > 1) && contentFlick.movingVertically

            orientation: Qt.Vertical
            color: "#3a3a3a"
        }
    }

    GraphView {
        id: graphView

        x: __verticalAxis.offset

        width: contentFlick.width
        height: (150 - __horizontalAxis.offset) / 2
        lineWidth: 1
        color: "orange"

        graph: graphContent

        anchors.bottom: contentFlick.top

        Rectangle {
            color: "gray"
            opacity: 0.35

            x: parent.width * contentFlick.visibleArea.xPosition
            width: parent.width * contentFlick.visibleArea.widthRatio

            y: parent.height * contentFlick.visibleArea.yPosition
            height: parent.height * contentFlick.visibleArea.heightRatio
        }
    }
}

