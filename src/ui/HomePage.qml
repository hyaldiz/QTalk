import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

import QTalk
import QTalk.Controls

Item {
    id: root
    anchors.fill: parent

    readonly property string hintText: qsTr("Please select LLM file")

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
        text: root.hintText
        anchors.top: selectFileButton.bottom
        anchors.topMargin: 8
        anchors.horizontalCenter: selectFileButton.horizontalCenter
        color: QTalk.palette.TextSolarized
        font.pixelSize: 14
        opacity: 0.95
    }

    FileDialog {
        id: fileDialog
        title: root.hintText

        nameFilters: ["Text files (*.txt)", "JSON files (*.json)", "All files (*)"]

        onAccepted: {
            QTalk.chatManager.chatEngine.load(fileDialog.file)
            //console.log("Seçilen dosya:", fileDialog.file)
        }

        onRejected: {
        }
    }
}
