import QTalk
import QTalk.Controls

import QtQuick.Layouts

ApplicationWindow {
    visible: true

    width: 800
    height: 480

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12

        ChatThread {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ChatInput {
            Layout.preferredWidth: parent.width*0.9
            Layout.preferredHeight: 80
            Layout.alignment: Qt.AlignCenter
        }
    }
}
