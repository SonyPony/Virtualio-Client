import QtQuick 2.0

Rectangle {
    id: stackBar

    property var stack: new Array

    function foo() {
        var nextMinimized = false

        for(var key in stackBar.stack) {
            var window = stackBar.stack[key]

            console.log(window.tabName.search(" |"))
            if(window.tabName.search("|") <= 0 && key + 1 < stackBar.stack.length) {
                console.log(key, stackBar.stack[key])
                if(stackBar.stack[parseInt(key) + 1].state === "minimized")
                    window.tabName = window.tabName + " |"
                //else
                  //  window.tabName -= " |"
            }
        }
    }

    function registerWindow(window) {
        for(var key in stackBar.stack)
            if(stackBar.stack[key] == window)
                return false

        if(stackBar.stack.length) {
            var previousTab = stackBar.stack[stackBar.stack.length - 1]
            window.minimizedPos = Qt.point(previousTab.x + previousTab.minimizedSize.width, stackBar.y)
        }

        else
            window.minimizedPos = Qt.point(0, stackBar.y)
        window.stateChanged.connect(foo)
        stackBar.stack.push(window)
        return true
    }
}

