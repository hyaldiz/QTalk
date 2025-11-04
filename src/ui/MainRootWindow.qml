import QTalk
import QTalk.Controls

import QTalk.UI

ApplicationWindow {
    visible: true

    width: 800
    height: 480

    //flags: Qt.FramelessWindowHint
    color: QTalk.palette.AppBackground

    Loader {
        id: mainLoader

        anchors.fill: parent

        source: "qrc:/qml/QTalk/UI/SplashScreen.qml"
    }
}
