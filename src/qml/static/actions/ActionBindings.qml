import QtQuick 2.5
import WebsocketClient 1.0
import ModuleState 1.0
import AppStates 1.0

Item {
    // ------------CONNECTION ACTIONS----------
    Connections {
        target: ipDialog
        onIpEntered: {
            websocketClient.url = "ws://" + ip + ":8888"
            websocketClient.reconnect()
        }

        onTimeout: {
            console.log("timeout")
            websocketClient.close()
        }
    }


    Connections {
        target: websocketClient
        onStatusChanged: {
            if(status == WebsocketClient.Open) {
                console.log("connected", AppStates.Connected)
                AppInfo.connectionState = AppStates.Connected
                websocketClient.sendTextMessage(messageManager.verificationRequestMsg())
            }

            else {
                AppInfo.connectionState = AppStates.Disconnected
                welcomeTab.setModuleState("VIO board", ModuleState.Discconnected)
            }
        }

        onTextMessageReceived: {
            console.log("received", message)
            messageManager.handleMessage(JSON.parse(message))
        }
    }

    Connections {
        target: messageManager
        onVerified: {
            console.log("verified!!!!!!")
            welcomeTab.setModuleState("VIO board", ModuleState.Connected)
            ipDialog.hide()
        }

        onReadDigitalPin: {
            var value = "ST: %1"
            layoutTab.setTagValue(pin, "FUNW", value.arg(parseInt(pinState)))
        }
    }
    // ----------------------------------------

    // -------------PROJECT ACTIONS------------
    Shortcut {
        context: Qt.ApplicationShortcut
        sequence: "Ctrl+S"
        onActivated: ProjectActions.saveProject(layoutTab.tagsLayout(), scriptTab.code)
    }

    Connections {
        target: ProjectActions
        onLayoutDataLoaded: {
            tabs.moveToTab(1)
            layoutTab.clearTags()
            layoutTab.createTags(data)
        }

        onScriptLoaded: scriptTab.code = code
        onCreateNewProject: {
            fileDialog.selectFolder = true
            fileDialog.visible = true
        }
    }

    Connections {
        target: fileDialog
        onAccepted: {
            if(!fileDialog.selectFolder) {
                ProjectActions.loadProjectFile(fileDialog.fileUrl)
                welcomeTab.addProject(fileDialog.fileUrl)
            }

            else {
                ProjectActions.setProjectName("Foo")
                ProjectActions.setProjectFolder(fileDialog.folder)
                ProjectActions.saveProject(layoutTab.tagsLayout(), scriptTab.code)
                welcomeTab.addProject(fileDialog.folder + "/Foo.pro")
            }
        }
    }

    Connections {
        target: welcomeTab
        onNewProject: ProjectActions.createNewProject()

        onOpenProject: {
            fileDialog.nameFilters = ["Project file (*.pro)"]
            fileDialog.selectFolder = false
            fileDialog.visible = true
        }
    }
    // ----------------------------------------

    // ---------------APP ACTIONS--------------
    Connections {
        target: tabs
        onCurrentTabChanged: {
            var isInEditableTabs = (tabs.currentTab == 1 || tabs.currentTab == 2)
            if(isInEditableTabs && AppInfo.mode != AppStates.Running) {
                playButton.enabled = true
                stopButton.enabled = false
            }

            else if(!isInEditableTabs && AppInfo.mode != AppStates.Running) {
                playButton.enabled = false
                stopButton.enabled = false
            }
        }
    }

    Connections {
        target: AppInfo
        onModeChanged: {
            if(AppInfo.mode == AppStates.Running) {
                playButton.enabled = false
                stopButton.enabled = true
                layoutTab.setTagsLock(true)
            }

            else {
                var isInEditableTabs = (tabs.currentTab == 1 || tabs.currentTab == 2)
                playButton.enabled = isInEditableTabs
                stopButton.enabled = false
                layoutTab.setTagsLock(false)
                websocketClient.sendTextMessage(messageManager.stopMsg())
            }
        }
    }

    Connections {
        target: playButton
        onClicked: {
            AppInfo.mode = AppStates.Running

            var tags = layoutTab.tagsFunction()
            for(var i in tags) {
                // TODO add options
                var tag = tags[i]

                if(tag["name"] == "UARTTX") {
                    websocketClient.sendTextMessage(messageManager.initPinMsg(
                        tag["pin"],
                        tag["name"],
                        tag["options"]["Baud rate"],
                        tag["options"]["Parity"],
                        tag["options"]["Stop bits"]
                    ))
                }

                else
                    websocketClient.sendTextMessage(messageManager.initPinMsg(tag["pin"], tag["name"]))
            }

            websocketClient.sendTextMessage(messageManager.initDoneMsg())
            websocketClient.sendTextMessage(messageManager.codeMsg(scriptTab.code))
        }
    }

    Connections {
        target: stopButton
        onClicked: {
            AppInfo.mode = AppStates.Stopped
        }
    }

    Connections {
        target: messageManager
        onError: {
            console.log("error", msg)
            messageDialog.error(msg)
        }
    }

    Connections {
        target: layoutTab
        onControlValueChanged: {
            var info = layoutTab.selectedTagInfo()
            var pinType = info["pinType"]

            if(pinType == "GPO")
                websocketClient.sendTextMessage(messageManager.setPinMsg(info["pin"], value))
            else if(pinType == "UTX") {
                var msg = messageManager.sendCharMsg(info["pin"], value)

                if(msg != "") {
                    var parsedMsg = JSON.parse(msg)
                    layoutTab.addMsg(info["options"]["Object name"], parsedMsg["value"], 230)
                    websocketClient.sendTextMessage(msg)
                }
            }

        }
    }

    // ----------------------------------------
}

