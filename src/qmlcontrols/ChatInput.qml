import QtQuick
import QtQuick.Controls

Rectangle {
    id: chatInput
    height: 55
    width: parent.width * 0.9
    radius: 10
    color: "#303030"

    function clamp(v, a, b) { return Math.max(a, Math.min(b, v)) }

    function updateLayout() {
        if (messageField.implicitHeight <= fl.height) {
            messageField.y = Math.max(0, (fl.height - messageField.implicitHeight) / 2)
            fl.contentY = 0
            return
        }

        messageField.y = 0

        const r = messageField.cursorRectangle
        const cursorTop = r.y
        const cursorBottom = r.y + r.height

        const viewTop = fl.contentY
        const viewBottom = fl.contentY + fl.height

        let newContentY = fl.contentY
        if (cursorTop < viewTop) {
            newContentY = cursorTop
        }
        else if (cursorBottom > viewBottom) {
            newContentY = cursorBottom - fl.height
        }

        const maxY = Math.max(0, fl.contentHeight - fl.height)
        fl.contentY = clamp(newContentY, 0, maxY)
    }

    Flickable {
        id: fl
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: sendButton.left
        anchors.margins: 10

        contentWidth: width
        contentHeight: Math.max(height, messageField.implicitHeight)
        interactive: messageField.implicitHeight > height

        onHeightChanged: chatInput.updateLayout()
        onContentHeightChanged: chatInput.updateLayout()

        TextArea {
            id: messageField
            width: parent.width
            wrapMode: TextArea.Wrap
            placeholderText: qsTr("Ask something")
            color: "white"
            font.pixelSize: 15
            selectByMouse: true
            background: Rectangle { color: "transparent" }

            readonly property int padd: topPadding + bottomPadding
            implicitHeight: Math.ceil(contentHeight) + padd

            onImplicitHeightChanged: chatInput.updateLayout()
            onCursorRectangleChanged: chatInput.updateLayout()
            onTextChanged: chatInput.updateLayout()
            onWidthChanged: chatInput.updateLayout()
            onActiveFocusChanged: chatInput.updateLayout()

            Keys.onPressed: (event) => {
                const enter = (event.key === Qt.Key_Return || event.key === Qt.Key_Enter)
                if (enter && !(event.modifiers & Qt.ShiftModifier)) {
                    event.accepted = true
                    chatInput.sendMessage()
                    messageField.clear()
                }
            }
        }
    }

    QTKIconButton {
        id: sendButton
        height: parent.height * 0.8
        width: height
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 8
        icon.path: ScreenTools.iconSend
        onClicked: chatInput.sendMessage()
    }

    function sendMessage() {
        console.log("Send Message")
    }

    Component.onCompleted: updateLayout()
}
