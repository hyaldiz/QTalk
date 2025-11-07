target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        ChatEngineTest.h
        ChatEngineTest.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
