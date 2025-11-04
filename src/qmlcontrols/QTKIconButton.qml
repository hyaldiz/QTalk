import QtQuick

import QTalk

Rectangle {
    id: control

    property alias icon: icon
    property color bgColor: QTalk.palette.ControlsBackground
    property color hoverColor: QTalk.palette.ControlsBackground

    signal clicked

    width: 60
    height: 60

    color: mouseArea.containsMouse ? hoverColor : bgColor
    radius: 100
    opacity: mouseArea.containsMouse ? 0.8 : 1

    QTKIcon {
        id: icon
        sourceSize.height: parent.height * 0.5
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            control.clicked()
        }

        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
}
