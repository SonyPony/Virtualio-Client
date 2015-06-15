import QtQuick 2.0

Item {
    id: progressBar

    property int value: 50
    property int minimum: 0
    property int maximum: 100
    property color themeColor
    property color edgeColor
    property int numberOfParticles: 5

    clip: true

    Rectangle {
        color: "transparent"
        border.color: parent.edgeColor

        width: parent.width
        height: parent.height + 2 * border.width

        anchors.centerIn: parent
    }

    Rectangle {
        id: filledPart

        color: themeColor
        clip: true

        width: parent.width * value / 100
        height: parent.height / 2
        anchors.verticalCenter: parent.verticalCenter

        //------------------PARTICLES------------------
        Row {
            spacing: 10
            anchors.verticalCenter: parent.verticalCenter
            Repeater {
                model: numberOfParticles
                delegate: Rectangle {
                    id: particle

                    color: "white"

                    height: progressBar.height / 4
                    width: height

                    //---------------MOVE ANIMATION----------------
                    NumberAnimation {
                        target: particle
                        property: "x"
                        from: -(numberOfParticles - modelData) * (10/*spacing*/ + particle.width)
                        to: progressBar.width + modelData * (10/*spacing*/ + particle.width)//filledPart.width + modelData * (10/*spacing*/ + particle.width)
                        duration: 1000
                        loops: Animation.Infinite
                        running: true
                    }
                    //---------------------------------------------
                }
            }
        }
        //---------------------------------------------
    }
}

