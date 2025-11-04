import QtQuick
import QtQuick.Controls

import QTalk

Item {
    id: chatBubble

    property bool sender: ID === QTalk.chatManager.mainUser.ID

    width: ListView.view ? ListView.view.width : 0
    height: bubble.height

    Rectangle {
        id: bubble
        width: Math.min(messageText.implicitWidth + 24, (chatBubble.width * 0.8))
        height: messageText.implicitHeight + 24
        x: chatBubble.sender ? 0 : chatBubble.width - width
        radius: 12
        color: failed ? QTalk.palette.BubleFailed
                      : chatBubble.sender ? QTalk.palette.BubleMainUser : QTalk.palette.BubleQTalk

        TextEdit {
            id: messageText
            anchors.fill: parent
            anchors.margins: 12

            readOnly: true
            selectByMouse: true

            wrapMode: TextEdit.Wrap

            color: QTalk.palette.Text
            text: contents
            font.pixelSize: 15
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignLeft
        }
    }
}
