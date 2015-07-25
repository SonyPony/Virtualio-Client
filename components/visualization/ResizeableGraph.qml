import QtQuick 2.0
import GraphAxis 1.0
import GraphContent 1.0

Item {
    id: component
    clip: true

    /*Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 1
        border.color: "orange"
    }*/

    Flickable {
        id: verticalFlick

        width: verticalAxis.width
        height: parent.height - horizontalAxis.offset
        contentWidth: verticalAxis.width
        contentHeight: verticalAxis.height
        contentY: contentFlick.contentY

        interactive: false
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        GraphAxis {
            id: verticalAxis

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

    Flickable {
        id: horizontalFlick

        x: verticalAxis.offset + verticalFlick.x
        y: component.height - horizontalAxis.height
        width: parent.width - verticalAxis.offset
        height: horizontalAxis.height
        contentWidth: horizontalAxis.width
        contentHeight: horizontalAxis.height
        contentX: contentFlick.contentX

        interactive: false
        flickableDirection: Flickable.HorizontalFlick
        boundsBehavior: Flickable.StopAtBounds

        GraphAxis {
            id: horizontalAxis

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
        width: horizontalFlick.width
        height: verticalFlick.height
        contentWidth: graphContent.width
        contentHeight: graphContent.height

        clip: true
        boundsBehavior: Flickable.StopAtBounds

        GraphContent {
            id: graphContent

            color: "#45C8DC"
            lineWidth: 1
            contentY: contentFlick.contentY

            dataY: [10, 20, 30, 60]
            dataX: [10, 20, 40 , 60]
            verticalAxis: verticalAxis
            horizontalAxis: horizontalAxis
        }
    }
}

