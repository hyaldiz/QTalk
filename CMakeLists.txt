cmake_minimum_required(VERSION 3.25)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/cmake/modules
)

# ----------------------------------------------------------------------------
# Default Build Type
# ----------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (Debug or Release)" FORCE)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available configuration types" FORCE)
    message(STATUS "No build type specified. Defaulting to Release.")
endif()

# ----------------------------------------------------------------------------
# CMake Policy Configuration
# ----------------------------------------------------------------------------
set(CMAKE_REQUIRED_QUIET ON)
set(CMAKE_POLICY_VERSION_MINIMUM ${CMAKE_MINIMUM_REQUIRED_VERSION})


include(Toolchain)
include(CustomOptions)
include(Git)

if(NOT QTK_BUILD_TESTING)
    set(BUILD_TESTING OFF CACHE INTERNAL "Default testing by default" FORCE)
endif()

project(${QTK_APP_NAME}
    VERSION ${QTK_APP_VERSION}
    DESCRIPTION ${QTK_APP_DESCRIPTION}
    LANGUAGES C CXX
)

find_package(Qt6
    REQUIRED
        COMPONENTS
        Core
        Gui
        Widgets
        Concurrent
        Qml
        QmlIntegration
        QuickControls2
        QuickWidgets
        Quick
    OPTIONAL_COMPONENTS
        Test
)

# ----------------------------------------------------------------------------
# Qt Policies (Enable modern Qt6 behaviors)
# ----------------------------------------------------------------------------
qt_policy(
    SET QTP0001 NEW  # Modern resource handling
    SET QTP0002 NEW  # New behavior for QML module URI
    SET QTP0003 NEW  # Better QML type registration
    SET QTP0004 NEW  # Improved translation handling
    SET QTP0005 NEW  # Enhanced deployment handling
)

list(APPEND QTK_RESOURCES
    "${CMAKE_SOURCE_DIR}/qtkresources.qrc"
)

qt_add_executable(${CMAKE_PROJECT_NAME}
    ${QTK_RESOURCES}
)

qt_add_qml_module(${CMAKE_PROJECT_NAME}
    URI QTK
    VERSION 1.0
    RESOURCE_PREFIX /qml
    IMPORTS
        QtQuick
        QtQuick.Controls
        QtQuick.Window
)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/llama.cpp)
add_subdirectory(src)

if(QTK_BUILD_TESTING)
    add_subdirectory(test)
    set_property(DIRECTORY test PROPERTY QT_EXCLUDE_FROM_TRANSLATION ON)
endif()
