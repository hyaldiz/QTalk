import QtQuick
import QtQuick.Controls

Rectangle {
    id: chatThread

    ListModel {
        id: model
        ListElement { sender: true ; message: "Selam"}
        ListElement { sender: false ; message: "Selam"}
        ListElement { sender: true ; message: "Bugün günlerden ne?"}
        ListElement { sender: true ; message: "Söyler misin?"}
        ListElement { sender: false ; message: "Cuma saat 15:07"}
    }

    Component.onCompleted: {
        openedChatList.model = model
    }

    ListView {
        id: openedChatList
        anchors.fill: parent
        anchors.margins: 16

        spacing: 8
        clip: true
        highlightFollowsCurrentItem: true

        onCountChanged: {
            openedChatList.currentIndex = count - 1
        }

        delegate: ChatBubble {}

        add: Transition{
            NumberAnimation{ properties: "x"; from: openedChatList.width/2; duration: 1500; easing.type: Easing.OutBounce; }
        }
    }
}
