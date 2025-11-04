qt_add_library(QTalkUIModule STATIC)

qt_add_qml_module(QTalkUIModule
    URI QTalk.UI
    VERSION 1.0
    RESOURCE_PREFIX /qml
    QML_FILES
    SplashScreen.qml
    HomePage.qml
    ChatPage.qml
)
