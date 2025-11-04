import QtQuick
import QtQuick.Controls // StackView'i kullanmak için bu import gerekli
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
                nameFilters: QTalk.corePlugin.supportedLLMExtensions

                onAccepted: {
                    root.modelFile = fileDialog.selectedFile

                    homeStackView.replace(checkSelectedModelComponent)
                }

                onRejected: {

                }
            }
        }
    }

    Component {
        id: checkSelectedModelComponent
        Item {
            anchors.fill: parent

            QTKBusyIndicator {
                anchors.centerIn: parent
                size: 96
                busy: !QTalk.chatManager.chatEngine.ready
            }

            Connections {
                target: QTalk.chatManager.chatEngine

                function onReadyChanged(ready) {
                    if(ready) {
                    }
                }

                function onError(message) {
                    homeStackView.replace(selectFileComponent)
                }
            }

            Component.onCompleted: {
                QTalk.chatManager.chatEngine.load(root.modelFile)
            }
        }
    }

    QTKStackView {
        id: homeStackView

        initialItem: selectFileComponent
    }
}
