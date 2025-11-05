import QTalk
import QTalk.Controls
import QTalk.UI


ApplicationWindow {
    id: mainWindow

    visible: true
    width: 800
    height: 480
    flags: Qt.FramelessWindowHint
    color: QTalk.palette.AppBackground

    header: MainRootWindowHeader {

    }

    Loader {
        id: mainLoader

        anchors.fill: parent

        source: "qrc:/qml/QTalk/UI/SplashScreen.qml"
    }

    MainWindowResizer {

    }

    // DropShadow {
    //   anchors.fill: rect
    //   horizontalOffset: 2
    //   verticalOffset: 2
    //   radius: 5
    //   samples: 5
    //   source: rect
    //   color: "black"
    // }
}
