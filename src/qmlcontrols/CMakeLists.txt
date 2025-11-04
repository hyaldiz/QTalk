target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    QTKPalette.h
    QTKPalette.cpp
    QTalkQmlGlobal.h
    QTalkQmlGlobal.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_library(QTalkControlsModule STATIC)

set_source_files_properties(ScreenTools.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(QTalkControlsModule
    URI QTalk.Controls
    VERSION 1.0
    RESOURCE_PREFIX /qml
    QML_FILES
    ChatBubble.qml
    ChatThread.qml
    ChatInput.qml
    QTKIconButton.qml
    QTKIcon.qml
    QTKBusyIndicator.qml
    ScreenTools.qml
)
