if(NOT QTK_BUILD_TESTING)
    return()
endif()

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        UnitTestList.h
        UnitTestList.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Test)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Test)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE QTK_UNITTEST_BUILD)

include(CTest)

# Custom target for running all tests
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure .    #make check -> ctest --output-on failure .
    USES_TERMINAL
    COMMENT "Running all QTalk unit tests"
)

function(add_qtk_test test_name)
    add_test(
        NAME ${test_name}
        COMMAND $<TARGET_FILE:${PROJECT_NAME}> --unittest:${test_name}
    )
    add_dependencies(check ${PROJECT_NAME})
endfunction()

add_subdirectory(qtkunittest)

add_subdirectory(chat)
add_qtk_test(ChatEngineTest)
