import QtQuick 2.0

Item {
    id: animation

    property int lineWidth: 2
    property color outerColor: "orange"

    function drawParts(space, numberOfPieces, color, ctx, size) {
        var center = Qt.point(size.width / 2, size.height / 2)
        var pieceSize = (2 * Math.PI) / numberOfPieces


        ctx.strokeStyle = color
        ctx.lineWidth = animation.lineWidth

        for(var i = 0; i < numberOfPieces; i++) {
            ctx.beginPath()
            ctx.arc(center.x, center.y, size.width / 2 - animation.lineWidth, i * pieceSize, (i + 1) * pieceSize - space)
            ctx.stroke()
            ctx.closePath()
        }
    }

    Canvas {
        id: outerCanvas
        anchors.fill: parent
        onPaint: animation.drawParts(Math.PI / 8, 5, "gray", outerCanvas.getContext("2d"), Qt.size(outerCanvas.width, outerCanvas.height))

        RotationAnimation { target: outerCanvas; from: 0; to: 360; duration: 2000; running: true; loops: Animation.Infinite }
    }

    Canvas {
        id: innerCanvas
        width: parent.width * 0.7
        height: parent.height * 0.7
        anchors.centerIn: parent
        onPaint: animation.drawParts(Math.PI / 4, 3, "#007ACC", innerCanvas.getContext("2d"), Qt.size(innerCanvas.width, innerCanvas.height))

        RotationAnimation { target: innerCanvas; from: 360; to: 0; duration: 1500; running: true; loops: Animation.Infinite }
    }
}


