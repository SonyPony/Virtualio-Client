import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import SerialCommunication 1.0
import "components/window" as Windows
import "components/animations" as Animations

Windows.StyledWindow {
    id: rootWindow

    width: 640
    height: 480
    visible: true
    color: "white"

    property var vars: new Array

    onXChanged: console.log(x)

    SerialCommunication {
        portIdentifier: "px4"
        onMessage: {
            var data = Formater.formatCapacitance(arg)
            //console.log(data)


            if(data[0] === "Capacitance measure") {
                capacitanceText.text = (parseInt(data[1]) + 1) + "/3"
                loading.opacity = 1
            }

            if(data[0] === "Capacitance") {
                capacitanceText.text = data[1]
                loading.opacity = 0
                console.log("Finished: ", data[1])
            }
        }
        Component.onCompleted: tryConnect()
        onConnectedChanged: console.log("Connection: ", connected)
        onError: console.log(arg)
    }

    Windows.StackBar {
        id: stackBar

        color: "#007ACC"
        height: 20
        width: parent.width

        anchors.bottom: parent.bottom
    }

    Windows.SubWindow {
        id: ff
        width: 100
        height: 100
        x: 300
        tabName: "FooBar"

        Component.onCompleted: stackBar.registerWindow(ff)
    }

    //Capacitance subwindow - TEST
    Windows.SubWindow {
        id: subwindow

        width: 250
        height: 250
        tabName: "Capacitance"

        Component.onCompleted: stackBar.registerWindow(subwindow)

        Animations.LoadingAnimation {
            id: loading
            width: 200
            height: 200
            anchors.centerIn: parent

            Behavior on opacity {
                NumberAnimation { duration: 400 }
            }
        }

        Text {
            id: capacitanceText
            text: "0/3"
            color: "gray"

            font.pixelSize: 40
            font.family: "Trebuchet MS"

            anchors.centerIn: parent
        }
    }
}
