import QtQuick 2.0

MouseArea {
    id: area

    property point clickPos
    property size delta
    property point areaPosition

    cursorShape: Qt.SizeHorCursor

    onPressed: clickPos = Qt.point(mouse.x, mouse.y)
    onPositionChanged: {
        delta = Qt.size(mouse.x - clickPos.x, mouse.y - clickPos.y)
        clickPos = Qt.point(mouse.x, mouse.y)
    }

    Component.onCompleted: reposition()

    function reposition() {
        x = areaPosition.x
        y = areaPosition.y
    }

    states: [
        State {
            name: "horizontal"
            PropertyChanges { target: area; cursorShape: Qt.SizeHorCursor }
        },

        State {
            name: "vertical"
            PropertyChanges { target: area; cursorShape: Qt.SizeVerCursor }
        },

        State {
            name: "corner"
            PropertyChanges { target: area; cursorShape: Qt.SizeFDiagCursor }
        }
    ]
}

