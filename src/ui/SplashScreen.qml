import QtQuick

import QTalk
import QTalk.Controls

Item {
    id: root

    property bool done: false

    QTKBusyIndicator {
        anchors.centerIn: parent
        size: 96
        busy: !root.done
    }

    Timer {
        interval: 3000
        running: true

        onTriggered: {
            root.done = true
        }
    }

    onDoneChanged: {
        mainLoader.source = "qrc:/qml/QTalk/UI/HomePage.qml"
    }

    Text {
        id: versionLabel

        anchors.right: parent.right
        anchors.bottom: parent.bottom

        anchors.margins: 10

        text: QTalk.appVersion

        color: QTalk.palette.TextSolarized
        font.pixelSize: 12
    }
}
