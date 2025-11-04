import QtQuick
import QtQuick.Controls

import QTalk
import QTalk.Controls

Item {
    id: chatThread

    ListView {
        id: openedChatList
        anchors.fill: parent
        anchors.margins: 16

        spacing: 8
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        highlightFollowsCurrentItem: true
        model: QTalk.chatManager.openedChatUser.messages

        onCountChanged: {
            openedChatList.currentIndex = count - 1
        }

        delegate: ChatBubble {}
    }
}
