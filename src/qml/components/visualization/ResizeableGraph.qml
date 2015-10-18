import QtQuick 2.0
import GraphAxis 1.0
import GraphContent 1.0
import GraphView 1.0
import NonInteractiveScrollBar 1.0

Item {
    id: component
    //clip: true

    Item {
        id: verticalFlick
        width: verticalAxis.width
        height: parent.height - horizontalAxis.offset
        clip: true

        GraphAxis {
            id: verticalAxis

            y: -contentFlick.contentY
            width: component.width
            height: component.height - horizontalAxis.offset
            color: Qt.rgba(0.95, 0.95, 0.95, 1)

            font: "Helvetica"
            textColor: "lightGray"
            fontSize: 10
            lineWidth: 1

            textMode: GraphAxis.ExcludeFirstAndLast
            values: Core.interval(0, 60)
            valuesCount:  4
            enabledDirections: GraphAxis.Vertical
            Component.onCompleted: verticalAxis.ratio =  1
        }
    }

    Item {
        id: horizontalFlick

        x: verticalAxis.offset + verticalFlick.x
        y: component.height - horizontalAxis.height
        width: parent.width - verticalAxis.offset
        height: horizontalAxis.height
        clip: true

        GraphAxis {
            id: horizontalAxis

            x: -contentFlick.contentX
            width: component.width - verticalAxis.offset
            height: component.height

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
            Component.onCompleted: horizontalAxis.ratio =  1
        }
    }

    Flickable {
        id: contentFlick
        x: verticalAxis.offset
        width: component.width - verticalAxis.offset//horizontalFlick.width
        height: component.height - horizontalAxis.offset//verticalFlick.height
        contentWidth: graphContent.width
        contentHeight: graphContent.height

        clip: true
        boundsBehavior: Flickable.StopAtBounds

        GraphContent {
            id: graphContent

            color: "#45C8DC"
            lineWidth: 1
            //contentY: contentFlick.contentY

            dataY: [10, 20, 30, 60]
            dataX: [10, 20, 40 , 60]
            verticalAxis: verticalAxis
            horizontalAxis: horizontalAxis
        }
    }

    Item {
        x: contentFlick.x
        width: contentFlick.width
        height: contentFlick.height

        NonInteractiveScrollBar {
            position: contentFlick.width * contentFlick.visibleArea.xPosition
            height: 2
            width: contentFlick.visibleArea.widthRatio * contentFlick.width
            active: (horizontalAxis.ratio > 1) && contentFlick.movingHorizontally

            orientation: Qt.Horizontal
            color: "#3a3a3a"
            anchors.top: parent.bottom
        }

        NonInteractiveScrollBar {
            position: contentFlick.height * contentFlick.visibleArea.yPosition
            width: 2
            height: contentFlick.height * contentFlick.visibleArea.heightRatio
            active: (verticalAxis.ratio > 1) && contentFlick.movingVertically

            orientation: Qt.Vertical
            color: "#3a3a3a"
        }
    }

    /*GraphView {
        x: verticalAxis.offset

        width: contentFlick.width//(1000 - verticalAxis.offset) / 2
        height: (150 - horizontalAxis.offset) / 2
        lineWidth: 1
        lineColor: "orange"

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
    }*/
}

