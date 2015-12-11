import QtQuick 2.0
import CloneableTag 1.0
import TagableDIL 1.0
import QtQuick.Controls 1.2
import ScrollView 1.0

Item {
    id: component

    anchors.fill: parent

    CloneableTag {
       id: cloneTag

       x: 0
       y: 10
       width: height * 80. / 25.
       height: 18 * (f.height / 420.)

       onNewObject: {
           f.registerTag(object)
       }
    }

    ScrollView {
        id: sv
        x: 100
        y: 100
        width: component.width
        height: component.height
        color: "blue"
        backgroundColor: "gray"


        TagableDIL {
            id: f

            width: 1.5*714//height * (720. / 420.)
            height: 1.5*420//parent.height
        }
    }
}

