import QtQuick

import QTalk.Controls

Item {
    id: root
    anchors.fill: parent


    QTKBusyIndicator {
        anchors.centerIn: parent
        size: 96
        busy: true
    }
}
