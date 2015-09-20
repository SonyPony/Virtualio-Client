import QtQuick 2.0

Rectangle {
    property var action: function() {}
    property int size
    property Component icon

    width: height
    height: size

    Loader {
        sourceComponent: icon
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: action()
    }
}


