import QtQuick

import QTalk
import QTalk.Controls

Rectangle {
    id: headerBar
    width: parent.width
    height: 24
    color: QTalk.palette.QTalkBrand

    Text {
        anchors.centerIn: parent
        text: QTalk.appName
        color: QTalk.palette.Text
        font.pixelSize: 15
    }

    MouseArea {
        anchors.fill: parent
        z: 1
        onPressed: (mouse) => {
                       if (mouse.button === Qt.LeftButton) {
                           mainWindow.startSystemMove()
                       }
                   }
    }

    MouseArea {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: ScreenTools.resizeMargin
        anchors.leftMargin: ScreenTools.resizeMargin * 2
        z: Qt.SizeBDiagCursor
        cursorShape: Qt.SizeVerCursor
        onPressed: (mouse) => {
                       if (mouse.button === Qt.LeftButton) {
                           mainWindow.startSystemResize(Qt.TopEdge)
                       }
                   }
    }

    MouseArea {
        anchors.left: parent.left
        anchors.top: parent.top
        width: ScreenTools.resizeMargin * 2
        height: ScreenTools.resizeMargin * 2
        z: Qt.SizeBDiagCursor
        cursorShape: Qt.SizeFDiagCursor
        onPressed: (mouse) => {
                       if (mouse.button === Qt.LeftButton) {
                           mainWindow.startSystemResize(Qt.TopEdge | Qt.LeftEdge)
                       }
                   }
    }

    MouseArea {
        anchors.right: parent.right
        anchors.top: parent.top
        width: ScreenTools.resizeMargin * 2
        height: ScreenTools.resizeMargin * 2
        z: QTalk.zOrderTopMost
        cursorShape: Qt.SizeBDiagCursor
        onPressed: (mouse) => {
                       if (mouse.button === Qt.LeftButton) {
                           mainWindow.startSystemResize(Qt.TopEdge | Qt.RightEdge)
                       }
                   }
    }

    Row {
        id: windowControls
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 1
        z: QTalk.zOrderWidgets

        QTKIconButton {
            id: minimizeBtn
            width: 40; height: parent.height
            radius: 0
            bgColor: QTalk.palette.QTalkBrand
            hoverColor: QTalk.palette.AppBackground
            icon.source: ScreenTools.iconWindowMinimize

            onClicked: {
                mainWindow.showMinimized()
            }
        }

        QTKIconButton {
            id: maximizeBtn
            width: 40; height: parent.height
            radius: 0
            bgColor: QTalk.palette.QTalkBrand
            hoverColor: QTalk.palette.AppBackground
            icon.source: ScreenTools.iconWindowMaximize

            onClicked: {
                if (mainWindow.visibility === Window.Maximized) {
                    mainWindow.showNormal();
                } else {
                    mainWindow.showMaximized();
                }
            }
        }

        QTKIconButton {
            id: closeBtn
            width: 40; height: parent.height
            radius: 0
            bgColor: QTalk.palette.Critical
            hoverColor: QTalk.palette.AppBackground
            icon.source: ScreenTools.iconQuit

            onClicked: {
                mainWindow.close()
            }
        }
    }
}
