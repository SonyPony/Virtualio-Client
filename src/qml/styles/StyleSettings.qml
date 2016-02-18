pragma Singleton
import QtQuick 2.0

QtObject {
    property color primaryColor: "#007ACC"
    property color secondaryColor: "#373a3a"
    property color ternaryColor: "#828586"

    property color primaryTextColor: "gray"
    property color secondaryTextColor: "#2392d0"
    property color ternaryTextColor: "white"

    property QtObject aboutPanel: QtObject {
        property color backgroundColor: "#f2f2f2"
        //SCHEMATIC
        property url schematicPath: "qrc:/resources/images/schematic.svg"
        //LABEL
        property string labelText: qsTr("ECOSYSTEM")
        property color labelColor: primaryColor
    }

    property QtObject tabSelection: QtObject {
        property color color: "#2f2f2f"
    }

    property QtObject codeEditor: QtObject {
        property color lineNumbersTextColor: "gray"
        property color lineNumbersColor: "#f2f2f2"
    }
}


