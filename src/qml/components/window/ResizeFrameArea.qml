import QtQuick 2.0

Item {
    id: frame

    property var window
    property int areaWidth: 2
    property size minimalSize: Qt.size(80, 80)
    property bool active: true
    property color color: "transparent"
    signal reposition

    anchors.fill: window

    onReposition: {
        top.reposition()
        r.reposition()
        horizontalArea.reposition()
        verticalArea.reposition()
        cornerArea.reposition()
    }

    //--------------RIGHT RESIZE AREA--------------
    ResizeArea {
        id: horizontalArea

        Rectangle {
            color: frame.color
            anchors.fill: parent
        }

        areaPosition: Qt.point(window.width - width, 0)
        state: "horizontal"
        enabled: frame.active
        height: window.height
        width: parent.areaWidth

        onDeltaChanged: if(window.width + delta.width > frame.minimalSize.width)
                            window.width += delta.width
        onReleased: frame.reposition()
    }
    //---------------------------------------------

    //--------------BOTTOM RESIZE AREA-------------
    ResizeArea {
        id: verticalArea

        Rectangle {
            color: frame.color
            anchors.fill: parent
        }

        areaPosition: Qt.point(0, window.height - height)
        state: "vertical"
        enabled: frame.active
        height: parent.areaWidth
        width: window.width

        onDeltaChanged: if(window.height + delta.height > frame.minimalSize.height)
                            window.height += delta.height
        onReleased: frame.reposition()
    }
    //---------------------------------------------

    //--------------CORNER RESIZE AREA-------------
    ResizeArea {
        id: cornerArea

        Rectangle {
            color: frame.color
            anchors.fill: parent
        }

        areaPosition: Qt.point(window.width - width, window.height - height)
        state: "corner"
        enabled: frame.active
        height: parent.areaWidth
        width: parent.areaWidth

        onReleased: frame.reposition()
        onDeltaChanged: {
            if(window.width + delta.width > frame.minimalSize.width)
                window.width += delta.width
            if(window.height + delta.height > frame.minimalSize.height)
                window.height += delta.height
        }
    }
    //---------------------------------------------

    ResizeArea {
        id: r
        property int t: 0
        Rectangle {
            color: frame.color
            anchors.fill: parent
        }

        areaPosition: Qt.point(0,0)
        state: "horizontal"
        enabled: frame.active
        height: parent.height
        width: 2

        onDeltaChanged: if(window.width + delta.width > frame.minimalSize.width) {
                            //window.width += delta.width
                            t-=delta.width
                            window.x += delta.width
                            window.width = window.width - delta.width
                            console.log("D", delta.width)
                            r.areaPosition = Qt.point(t, 0)
                            r.reposition()
                            //r.areaPosition = Qt.point(0,0)
                        }
        onReleased: {
            r.t = 0
            r.areaPosition = Qt.point(0,0)
            frame.reposition()
        }
    }

    ResizeArea {
        id: top
        property int t: 0
        Rectangle {
            color: frame.color
            anchors.fill: parent
        }

        areaPosition: Qt.point(0,0)
        state: "vertical"
        enabled: frame.active
        height: 2
        width: parent.width

        onDeltaChanged: if(window.height + delta.height > frame.minimalSize.height) {
                            //window.width += delta.width
                            t-=delta.height
                            window.y += delta.height
                            window.height = window.height - delta.height

                            top.areaPosition = Qt.point(0, t)
                            top.reposition()
                            //r.areaPosition = Qt.point(0,0)
                        }
        onReleased: {
            top.t = 0
            top.areaPosition = Qt.point(0,0)
            frame.reposition()
        }
    }
}

