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
        color: chatBubble.sender ? "gray" : "green"

        Text {
            id: messageText
            anchors.fill: parent
            anchors.margins: 12
            wrapMode: Label.Wrap
            color: "#ffffff"
            text: contents
            opacity: 0.75
            font.pixelSize: 12
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: chatBubble.sender ? Qt.AlignLeft : Qt.AlignRight
        }
    }
}
