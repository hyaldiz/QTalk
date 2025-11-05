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

    Image {
        id: emptyStateImage
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        visible: openedChatList.count === 0

        source: ScreenTools.iconCommunication

        SequentialAnimation {
            id: shakeAnimation

            loops: Animation.Infinite
            running: emptyStateImage.visible

            onRunningChanged: {
                if (!running) {
                    emptyStateImage.rotation = 0
                }
            }

            PropertyAnimation { target: emptyStateImage ; property: "rotation" ; to: -20; duration: 250; easing.type: Easing.InBounce }
            PropertyAnimation { target: emptyStateImage ; property: "rotation" ; to: 20; duration: 250; easing.type: Easing.InBounce }
            PropertyAnimation { target: emptyStateImage ; property: "rotation" ; to: -20; duration: 250; easing.type: Easing.InBounce }
            PropertyAnimation { target: emptyStateImage ; property: "rotation" ; to: 20; duration: 250; easing.type: Easing.InBounce }
            PropertyAnimation { target: emptyStateImage ; property: "rotation" ; to: 0; duration: 250; easing.type: Easing.InBounce }
            PauseAnimation { duration: 5000 }
        }
    }
}
