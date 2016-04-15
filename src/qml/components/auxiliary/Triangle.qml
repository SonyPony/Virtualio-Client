import QtQuick 2.0

Canvas {
    id: canvas

    property color color
    property bool inverted: false
    property bool rightAngle: false

    antialiasing: true
    onWidthChanged: requestPaint()
    onHeightChanged: requestPaint()

    onPaint: {
        var ctx = canvas.getContext('2d');

        ctx.clearRect(x, y, width, height)
        ctx.beginPath()
        ctx.fillStyle = canvas.color;

        if(!rightAngle) {
            ctx.moveTo(canvas.width * canvas.inverted, 0)
            ctx.lineTo(canvas.width * (!canvas.inverted), canvas.height / 2.)
            ctx.lineTo(canvas.width * canvas.inverted, canvas.height)
            ctx.lineTo(canvas.width * canvas.inverted, 0)
        }

        else {
            ctx.moveTo(canvas.width * canvas.inverted, 0)
            ctx.lineTo(canvas.width * (!canvas.inverted), canvas.height)
            ctx.lineTo(canvas.width * canvas.inverted, canvas.height)
            ctx.lineTo(canvas.width * canvas.inverted, 0)
        }

        ctx.fill()
        ctx.closePath()
    }
}
