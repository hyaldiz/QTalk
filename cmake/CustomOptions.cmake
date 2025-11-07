include(CMakeDependentOption)

set(QTK_APP_NAME "QTalk" CACHE STRING "App Name")
set(QTK_APP_COPYRIGHT "Copyright (c) 2025 Huseyin Yaldız. All rights reserved" CACHE STRING "Copyright")
set(QTK_APP_DESCRIPTION "QTalk llama.cpp based AI Chat" CACHE STRING "Description")

set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml" CACHE PATH "QML output directory")
set(QML_IMPORT_PATH "${QT_QML_OUTPUT_DIRECTORY}" CACHE STRING "Additional QML import paths")

option(QT_SILENCE_MISSING_DEPENDENCY_TARGET_WARNING "Silence missing dependency warnings" OFF)
option(QT_ENABLE_VERBOSE_DEPLOYMENT "Enable verbose deployment output" OFF)
option(QT_DEBUG_FIND_PACKAGE "Print search paths when package not found" ON)
option(QT_QML_GENERATE_QMLLS_INI "Generate qmlls.ini for QML language server" ON)

cmake_dependent_option(QTK_BUILD_TESTING "Enable unit tests" ON "CMAKE_BUILD_TYPE STREQUAL Debug" OFF)
