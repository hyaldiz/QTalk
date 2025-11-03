import QtQuick
import QtQuick.Controls

import QTalk
import QTalk.Controls

Rectangle {
    id: chatThread

    ListView {
        id: openedChatList
        anchors.fill: parent
        anchors.margins: 16

        spacing: 8
        clip: true
        highlightFollowsCurrentItem: true
        model: QTalk.chatManager.openedChatUser.messages

        onCountChanged: {
            openedChatList.currentIndex = count - 1
        }

        delegate: ChatBubble {}

        add: Transition{
            NumberAnimation{ properties: "x"; from: openedChatList.width/2; duration: 1500; easing.type: Easing.OutBounce; }
        }
    }
}
