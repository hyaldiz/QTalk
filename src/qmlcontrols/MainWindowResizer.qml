import QtQuick

import QTalk
import QTalk.Controls

Item {
    anchors.fill: parent

    z: QTalk.zOrderTopMost

    MouseArea {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: ScreenTools.resizeMargin
        cursorShape: Qt.SizeHorCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.LeftEdge)
            }
        }
    }

    MouseArea {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: ScreenTools.resizeMargin
        cursorShape: Qt.SizeHorCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.RightEdge)
            }
        }
    }

    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: ScreenTools.resizeMargin
        cursorShape: Qt.SizeVerCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.BottomEdge)
            }
        }
    }

    MouseArea {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: ScreenTools.resizeMargin * 2
        height: ScreenTools.resizeMargin * 2
        cursorShape: Qt.SizeBDiagCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.BottomEdge | Qt.LeftEdge)
            }
        }
    }

    MouseArea {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: ScreenTools.resizeMargin * 2
        height: ScreenTools.resizeMargin * 2
        cursorShape: Qt.SizeFDiagCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.BottomEdge | Qt.RightEdge)
            }
        }
    }
}
