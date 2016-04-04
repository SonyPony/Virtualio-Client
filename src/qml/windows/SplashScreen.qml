import QtQuick 2.5

Rectangle {
    visible: true

    color: "transparent"//"#F3F4F4"

    border.width: 1
    border.color: "#CCCCCB"

    FontLoader {
        id: helveticaThin
        source: "qrc:/resources/fonts/HelveticaNeue-Thin.otf"
    }

    Image {
        width: 30
        height: width

        source: "qrc:/resources/images/cross.svg"

        sourceSize.width: width
        sourceSize.height: width

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: height / 2
        anchors.rightMargin: height / 2

        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }

    Image {
        id: logo

        width: 350
        height: width

        source: "qrc:/resources/images/logo-virtualio.svg"

        sourceSize.width: width
        sourceSize.height: width

        anchors.top: parent.top
        anchors.topMargin: width / 8
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextMetrics {
        id: fm

        text: "VirtualIO"
        font: textVirtual.font
    }

    Item {
        width: fm.boundingRect.width

        Text {
            id: textVirtual

            text: "Virtual"
            color: "black"

            font.pointSize: 40
            font.family: helveticaThin.name
        }

        Text {
            text: "IO"
            color: "#00BEF1"

            font: textVirtual.font
            anchors.left: textVirtual.right
        }

        anchors.topMargin: -20
        anchors.top: logo.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        text: qsTr("Starting...")
        color: "#00BEF1"

        font.pointSize: 18
        font.family: helveticaThin.name

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: height / 2
        anchors.bottomMargin: height / 2
    }
}

