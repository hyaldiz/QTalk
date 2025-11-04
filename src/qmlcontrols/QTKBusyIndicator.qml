import QtQuick

import QTalk.Controls

Item {
    id: root
    property bool busy: false
    property url source: ScreenTools.iconQTalk
    property int size: 128

    width: size
    height: size

    Image {
        id: icon
        anchors.centerIn: parent
        width: root.size
        height: root.size
        source: root.source
        fillMode: Image.PreserveAspectFit
        opacity: 0.0
    }

    SequentialAnimation {
        id: startupFade
        running: false
        loops: 1
        NumberAnimation { target: icon; property: "opacity"; from: 0.0; to: 1.0; duration: 600; easing.type: Easing.InOutQuad }
        onStopped: {
            if (root.busy) pulse.running = true
        }
    }

    SequentialAnimation {
        id: pulse
        running: false
        loops: Animation.Infinite
        NumberAnimation { target: icon; property: "opacity"; from: 1.0; to: 0.4; duration: 900; easing.type: Easing.InOutQuad }
        NumberAnimation { target: icon; property: "opacity"; from: 0.4; to: 1.0; duration: 900; easing.type: Easing.InOutQuad }
    }

    onBusyChanged: {
        if (busy) {
            pulse.running = false
            startupFade.running = false
            startupFade.running = true
        } else {
            startupFade.running = false
            pulse.running = false
            icon.opacity = 0.0
        }
    }
}
