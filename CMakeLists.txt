cmake_minimum_required(VERSION 3.16)

project(QTalk VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LLAMA_NATIVE ON CACHE BOOL "" FORCE)
set(GGML_OPENMP ON CACHE BOOL "" FORCE)
set(LLAMA_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # statik tercih ediyorsan

find_package(Qt6 6.2 COMPONENTS Core Gui Qml Quick REQUIRED)

qt_add_executable(appQTalk
    src/main.cpp
    src/llama/LlamaWorker.h
    src/llama/LlamaWorker_p.h
    src/llama/LlamaWorker.cpp
    src/llama/LlamaWorker_p.cpp
    src/llama/ChatEngine.h
    src/llama/ChatEngine.cpp
)

qt_add_qml_module(appQTalk
    URI QTalk
    VERSION 1.0
    QML_FILES main.qml 
)

add_subdirectory(libs/llama.cpp)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQTalk PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQTalk
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appQTalk PRIVATE libs/llama.cpp)
target_link_libraries(appQTalk
    PRIVATE
      Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick
      llama                         # llama.cpp’nin oluşturduğu hedef
)

include(GNUInstallDirs)
install(TARGETS appQTalk
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
