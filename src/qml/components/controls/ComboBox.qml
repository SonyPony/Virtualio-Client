import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0

Item {
    id: component

    property bool dropMenuVisible: dropMenu.visible
    property int dropDownItemHeight: component.height
    property var model: [0, 1, 4, 5]
    property string currentItem: model[0]
    property int currentItemIndex: 0

    property Component comboButton: Rectangle {
        color: "transparent"
        border.color: "black"
        border.width: 1

        Text {
            text: currentItem
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
    }

    property Component dropDownMenuBackground: Rectangle {
        color: "transparent"
        border.color: "black"
        border.width: 1
    }

    property Component icon: Item {}

    property Component menuItem: Rectangle {
        color: (hovered) ?"lightBlue" :"transparent"

        Text {
            color: "black"
            text: itemData
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
    }

    // for loosing "focus"
    onDropMenuVisibleChanged: {
        if(dropMenuVisible) {
            rootMouseArea.enabled = true
            rootMouseArea.clicked.connect(dropMenu.hide)
        }

        else {
            rootMouseArea.enabled = false
            rootMouseArea.clicked.disconnect(dropMenu.hide)
        }
    }

    Loader {
        id: comboButton

        property bool dropMenuVisible: component.dropMenuVisible
        property string urrentItem: component.currentItem

        sourceComponent: component.comboButton
        anchors.fill: parent

        Loader {
            sourceComponent: component.icon
            width: height
            height: parent.height

            anchors.right: parent.right
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(dropMenu.visible)
                    dropMenu.hide()
                else
                    dropMenu.show()
            }
        }
    }

    Item {
        id: dropMenu

        signal show
        signal hide

        visible: false
        focus: visible
        width: component.width
        height: component.dropDownItemHeight * component.model.length
        clip: true
        anchors.top: comboButton.bottom

        Keys.onUpPressed: {
            if(currentItemIndex - 1 < 0)
                currentItemIndex = model.length - 1
            else
                currentItemIndex--
        }

        Keys.onDownPressed: {
            if(currentItemIndex + 1 >= model.length)
                currentItemIndex = 0
            else
                currentItemIndex++
        }

        Keys.onReturnPressed: {
            currentItem = model[currentItemIndex]
            dropMenu.hide()
        }

        onShow: SequentialAnimation {
            ScriptAction { script: { dropMenu.visible = true } }
            NumberAnimation {
                target: dropMenu
                property: "height"
                from: 0
                to: comboButton.height * component.model.length
                duration: 250
                easing.type: Easing.InOutQuad
            }
        }

        onHide: SequentialAnimation {
            NumberAnimation {
                target: dropMenu
                property: "height"
                from: comboButton.height * component.model.length
                to: 0
                duration: 250
                easing.type: Easing.InOutQuad
            }
            ScriptAction { script: { dropMenu.visible = false } }
        }

        Loader {
            sourceComponent: component.dropDownMenuBackground
            anchors.fill: parent
        }

        Column {
            Repeater {
                model: component.model
                delegate: Component {
                    Loader {
                        property var itemData: modelData
                        property bool hovered: (component.currentItemIndex == index)

                        sourceComponent: component.menuItem
                        x: 1
                        width: component.width - 2
                        // adding dependency on dropmenu height
                        height: dropMenu.height / component.model.length - Math.floor(index / (component.model.length - 1))
                        clip: true

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered: parent.hovered = true
                            onExited: parent.hovered = false
                            onClicked: {
                                dropMenu.hide()
                                currentItem = modelData
                            }
                        }
                    }
                }
            }
        }
    }
}
