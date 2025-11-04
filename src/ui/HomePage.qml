import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QTalk
import QTalk.Controls

Item {
    id: root
    anchors.fill: parent

    property url modelFile: ""

    Component {
        id: selectFileComponent
        Item {
            anchors.fill: parent

            readonly property string hintStr: qsTr("Please select LLM file")

            QTKIconButton {
                id: selectFileButton
                anchors.centerIn: parent
                width: 48; height: 48
                icon.path: ScreenTools.iconSelectFile
                onClicked: {
                    fileDialog.open()
                }
            }

            Text {
                id: hintText
                text: hintStr
                anchors.top: selectFileButton.bottom
                anchors.topMargin: 8
                anchors.horizontalCenter: selectFileButton.horizontalCenter
                color: QTalk.palette.TextSolarized
                font.pixelSize: 14
                opacity: 0.95
            }

            FileDialog {
                id: fileDialog
                title: hintStr

                nameFilters: ["(*.gguf)"]

                onAccepted: {
                    root.modelFile = fileDialog.selectedFile
                    mainLoader.sourceComponent = checkSelectedModelComponent
                }

                onRejected: {
                }
            }
        }
    }

    Component {
        id: checkSelectedModelComponent
        Item {
            QTKBusyIndicator {
                anchors.centerIn: parent
                size: 96
                busy: !QTalk.chatManager.chatEngine.ready
            }

            Connections {
                target: QTalk.chatManager.chatEngine
                function onReadyChanged(ready) {
                    if(ready) {
                        //push to chat
                        return
                    }
                }
            }

            Connections {
                target: QTalk.chatManager.chatEngine
                function onError(message) {
                    mainLoader.sourceComponent = selectFileComponent
                }
            }

            Component.onCompleted: {
                console.log("Model file: " + root.modelFile)

                QTalk.chatManager.chatEngine.load(root.modelFile)
            }
        }
    }

    Loader {
        id: mainLoader
        anchors.fill: parent
    }

    Component.onCompleted: {
        mainLoader.sourceComponent = selectFileComponent
    }
}
