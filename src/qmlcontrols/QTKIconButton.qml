import QtQuick

Rectangle {
    id: control

    property alias icon: icon

    signal clicked

    width: 60
    height: 60

    color: "#363636"
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
