qt_add_library(QTalkModule STATIC)

# ----------------------------------------------------------------------------
# QML Resources
# ----------------------------------------------------------------------------
set_source_files_properties(ui/MainRootWindow.qml
    PROPERTIES
        QT_RESOURCE_ALIAS MainRootWindow.qml
)

qt_add_qml_module(QTalkModule
    URI QTalk
    VERSION 1.0
    RESOURCE_PREFIX /qml
    QML_FILES
        ui/MainRootWindow.qml
    IMPORTS
        QTK
    NO_PLUGIN
)

qt_policy(SET QTP0004 NEW)

add_subdirectory(utilities)
add_subdirectory(llm)
add_subdirectory(api)
add_subdirectory(ui)
add_subdirectory(qmlcontrols)
add_subdirectory(chat)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    main.cpp
    AppMessages.h
    AppMessages.cpp
    QTKApplication.h
    QTKApplication_p.h
    QTKApplication.cpp
    QTKLoggingCategory.h
    QTKLoggingCategory.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::Concurrent
        Qt6::Qml
        Qt6::QmlIntegration
        Qt6::QuickControls2
        Qt6::QuickWidgets
        Qt6::Quick
        #QTK Modules
        QTalkModule
        QTalkControlsModule
        QTalkUIModule
)

set_target_properties(${CMAKE_PROJECT_NAME}
    PROPERTIES
    QT_RESOURCE_PREFIX "/qml"
    OUTPUT_NAME ${CMAKE_PROJECT_NAME}
)

target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE
        QTK_APP_NAME="${QTK_APP_NAME}"
        QTK_APP_VERSION_STR="${QTK_APP_VERSION_STR}"
)
