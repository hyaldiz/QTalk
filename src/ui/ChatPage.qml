import QtQuick
import QtQuick.Layouts

import QTalk.Controls

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12

        ChatThread {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ChatInput {
            Layout.fillWidth: true
            Layout.leftMargin: 12
            Layout.rightMargin: 12
            Layout.preferredHeight: 80
            Layout.alignment: Qt.AlignCenter
        }
    }
}
