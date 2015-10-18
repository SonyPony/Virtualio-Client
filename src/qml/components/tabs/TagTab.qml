import QtQuick 2.0
import CloneableTag 1.0
import TagableDIL 1.0

Item {
    anchors.fill: parent

    CloneableTag {
       id: cloneTag

       x: 20
       y: 10
       width: height * 80. / 25.
       height: 18 * (f.height / 420.)

       onNewObject: {
           f.registerTag(object)
       }
    }

    TagableDIL {
        id: f

        width: height * (720. / 420.)
        height: parent.height
    }
}

